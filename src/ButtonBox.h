//
// Created by yiwei yang on 2/12/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_BUTTONBOX_H
#define RYAN_TEACHING_WINTER_SESSION_BUTTONBOX_H

#include "engine/Work.h"
#include <functional>
#include <jngl/Drawable.hpp>
#include <jngl/sprite.hpp>
#include <string>

class Work;

class Widget : public jngl::Drawable {
public:
    [[nodiscard]] bool getSensitive() const;

    void setSensitive(bool);

    void setFocus(bool);

    virtual void onFocusChanged();

    virtual void onAdd(Work &);

protected:
    bool sensitive = true;
    bool focus = false;
};

class Button : public Widget {
public:
    Button(std::string text, std::function<void()> callback, const std::string &normal = "button",
           const std::string &mouseOver = "button_over", const std::string &clicked = "button_clicked");

    void SetText(const std::string &);

    void draw() const override;

    void step() override;

protected:
    jngl::Sprite spriteClicked;

private:
    std::string text_;
    int mouseoverAlpha_;
    std::function<void()> callback_;
    bool clicked_;
    jngl::Sprite sprite;
    jngl::Sprite spriteMouseOver;
    const static int fontSize_;
};

class ButtonBox : public Widget {
public:
    ButtonBox(); // Creates a box at the center of the screen
    ButtonBox(int xCenter, int yCenter);
    void add(const std::string &text, const std::function<void()> &);
    void draw() const override;
    void step() override;

    void onAdd(Work &) override;

private:
    std::vector<std::shared_ptr<Button>> buttons_;
    const int xCenter_, yCenter_;
    const static int spacing_;
};

class HiddenButton : public Button {
public:
    explicit HiddenButton(std::function<void()> callback, char key_, const std::string &normal = "clicked",
                          const std::string &mouseOver = "clicked", const std::string &clicked = "clicked");
    void step() override;
    void draw() const override;
    void Blink();
    void SetDown();

private:
    const char key_;
    char isDown_ =false;
};

#endif // RYAN_TEACHING_WINTER_SESSION_BUTTONBOX_H
