//
// Created by yiwei yang on 2/13/22.
//

#include "Input.h"

#include <jngl/all.hpp>

Input::Input(int x, int y) : x_(x), y_(y), password_(false), displayCursor_(0) {}

void Input::setMaxWidth(unsigned int width) { maxWidth = width; }

void Input::setPassword(bool password) { password_ = password; }

void Input::onFocusChanged() { displayCursor_ = 50; }

void Input::step() {
    if (!sensitive || !focus) {
        return;
    }
    --displayCursor_;
    if (displayCursor_ < -35 || !jngl::getTextInput().empty()) {
        displayCursor_ = 35;
    }
    text += jngl::getTextInput();
    if (jngl::keyPressed(jngl::key::BackSpace) && !text.empty()) {
        removeLastCharacter();
    }
    while (jngl::getTextWidth(text) > maxWidth) {
        removeLastCharacter();
    }
}

void Input::draw() const {
    std::string temp;
    if (password_) {
        temp = text;
        size_t size = text.size();
        text.clear();
        for (size_t i = 0; i < size; ++i) {
            text += "●";
        }
    }
    if (sensitive) {
        jngl::setFontColor(0, 0, 0);
    } else {
        jngl::setFontColor(150, 150, 150);
    }
    if (focus && displayCursor_ > 0) {
        jngl::print(text + "|", x_, y_);
    } else {
        jngl::print(text, x_, y_);
    }
    if (password_) {
        text = temp;
    }
}

std::string Input::getText() const { return text; }

void Input::setText(const std::string &text) { this->text = text; }

void Input::removeLastCharacter() {
    displayCursor_ = 50;
    auto it = text.end();
    --it;
    while (*it & 0x80 && !(*it & 0x40)) { // Unicode character?
        --it;
    }
    text.erase(it, text.end());
}
