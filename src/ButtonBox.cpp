//
// Created by yiwei yang on 2/12/22.
//

#include "ButtonBox.h"
#include "engine/Options.h"
#include "engine/Paths.h"
#include "engine/Screen.h"
#include <jngl/all.hpp>
#include <jngl/matrix.hpp>
#include <string>
#include <thread>
#include <utility>

extern bool clicked_wrong;

bool Widget::getSensitive() const { return sensitive; }

void Widget::setSensitive(const bool sensitive_) { this->sensitive = sensitive_; }

void Widget::setFocus(const bool focus_) {
    bool old = this->focus;
    this->focus = focus_;
    if (focus_ != old) {
        onFocusChanged();
    }
}

void Widget::onFocusChanged() {}

void Widget::onAdd(Work &) {}

const int Button::fontSize_ = 70;

Button::Button(std::string text, std::function<void()> callback, const std::string &normal,
               const std::string &mouseOver, const std::string &clicked)
    : text_(std::move(text)), mouseoverAlpha_(0), callback_(std::move(callback)), clicked_(false),
      sprite(getPaths().getGraphics() + normal), spriteMouseOver(getPaths().getGraphics() + mouseOver),
      spriteClicked(getPaths().getGraphics() + clicked) {
    width = sprite.getWidth() * jngl::getScaleFactor();
    height = sprite.getHeight() * jngl::getScaleFactor();
}

void Button::SetText(const std::string &text) { text_ = text; }

void Button::draw() const {
    int alpha = mouseoverAlpha_;
    if (clicked_) {
        alpha -= 100;
    }
    auto mv = jngl::modelview().translate(getCenter());
    sprite.draw(mv.scale(1.0f + (alpha / 6000.0f)));
    if (focus) {
        spriteMouseOver.draw(mv);
    }
    jngl::setSpriteColor(255, 255, 255, alpha);
    jngl::pushMatrix();
    spriteMouseOver.draw(mv.scale(1.0f + (alpha / 6000.0f)));
    jngl::popMatrix();
    jngl::setSpriteColor(255, 255, 255, 255);
    if (clicked_) {
        spriteClicked.draw(mv.scale(1.0f + (alpha / 6000.0f)));
    }
    jngl::setFontColor(255, 255, 255);
    jngl::setFontSize(fontSize_);
    if (!clicked_) {
        GetScreen().printCentered(text_, getCenter());
    } else {
        GetScreen().printCentered(text_, {getCenter().x + 5, getCenter().y + 5});
    }
}

void Button::step() {
    if (!jngl::mouseDown()) {
        clicked_ = false;
    }
    const int alphaSpeed = 20;
    if (focus) {
        if (jngl::keyPressed(jngl::key::Space) || jngl::keyPressed(jngl::key::Return)) {
            clicked_ = true;
            callback_();
        }
    }
    if (sensitive && contains(jngl::getMousePos())) {
        if (mouseoverAlpha_ < 255) {
            mouseoverAlpha_ += alphaSpeed;
        }
        if (jngl::mousePressed()) {
            clicked_ = true;
            callback_();
        }
    } else if (mouseoverAlpha_ > 0) {
        mouseoverAlpha_ -= alphaSpeed;
    }
    if (mouseoverAlpha_ > 255) {
        mouseoverAlpha_ = 255;
    }
    if (mouseoverAlpha_ < 0) {
        mouseoverAlpha_ = 0;
    }
}

const int ButtonBox::spacing_ = 30;

ButtonBox::ButtonBox(const int xCenter, const int yCenter) : xCenter_(xCenter), yCenter_(yCenter) {
    setSensitive(false);
}

ButtonBox::ButtonBox() : xCenter_(0), yCenter_(0) { setSensitive(false); }

void ButtonBox::add(const std::string &text, const std::function<void()> &function) {
    buttons_.push_back(std::make_shared<Button>(text, function));

    auto end = buttons_.end();
    int yPosButton = yCenter_ - (buttons_.size() * (buttons_[0]->getHeight() + spacing_) - spacing_) / 2 +
                     buttons_[0]->getHeight() / 2;
    for (auto it = buttons_.begin(); it != end; ++it) {
        (*it)->setCenter(xCenter_, yPosButton);
        yPosButton += buttons_[0]->getHeight() + spacing_;
    }
}

void ButtonBox::draw() const {}

void ButtonBox::step() {}

void ButtonBox::onAdd(Work &work) {
    for (auto &button : buttons_) {
        work.addWidget(button);
    }
}

HiddenButton::HiddenButton(std::function<void()> callback, char key_, int x, int y, const std::string &normal,
                           const std::string &mouseOver, const std::string &clicked)
    : Button("", std::move(callback), normal, mouseOver, clicked), key_(key_), x_(x), y_(y),
      normal_("../image/" + normal), clicked_("../image/" + clicked) {
    setSensitive(false);
    this->setCenter(x, y);
}

void HiddenButton::Blink() {
    for (int i = 0; i < 100; i++) {
        GetScreen().DrawCentered(clicked_, x_, y_);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        GetScreen().DrawCentered(normal_, x_, y_);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void HiddenButton::draw() const { Button::draw(); }

void HiddenButton::step() {
    //    Button::step();
    if (jngl::keyPressed(key_) && isDown_) {
        isDown_ = false;
        clicked_wrong = true;
        Blink();
        callback_();
    }
    if (!jngl::mouseDown()) {
        clicked_ = false;
    }
    const int alphaSpeed = 20;
    if (focus) {
        if (jngl::keyPressed(jngl::key::Space) || jngl::keyPressed(jngl::key::Return)) {
            if (isDown_) {
                clicked_wrong = true;
                Blink();
                clicked_ = true;
                callback_();
            }
        }
    }
    if (sensitive && contains(jngl::getMousePos())) {
        if (mouseoverAlpha_ < 255) {
            mouseoverAlpha_ += alphaSpeed;
        }
        if (jngl::mousePressed()) {
            if (isDown_) {
                clicked_wrong = true;
                Blink();
                clicked_ = true;
                callback_();
            }
        }
    } else if (mouseoverAlpha_ > 0) {
        mouseoverAlpha_ -= alphaSpeed;
    }
    if (mouseoverAlpha_ > 255) {
        mouseoverAlpha_ = 255;
    }
    if (mouseoverAlpha_ < 0) {
        mouseoverAlpha_ = 0;
    }
}

void HiddenButton::setDown() { isDown_ = true; }

SenPai::SenPai(std::function<void()> callback, int x, int y)
    : Button("", std::move(callback), getOptions().preimg, getOptions().preimg, getOptions().postimg) {}

void SenPai::step() {
    if (isDown_) {
        this->sensitive = true;
    } else {
        this->sensitive = false;
    }
    Button::step();
}

void SenPai::draw() const { Button::draw(); }

void SenPai::setDown() { isDown_ = true; }

void SenPai::setCenters(int x, int y) { this->setCenter(x, y); }
