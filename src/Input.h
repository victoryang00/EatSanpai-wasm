//
// Created by yiwei yang on 2/13/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_INPUT_H
#define RYAN_TEACHING_WINTER_SESSION_INPUT_H

#include "ButtonBox.h"

#include <string>
#include <vector>

class Input : public Widget {
public:
    Input(int x, int y);
    void step() override;
    void draw() const override;
    std::string getText() const;
    void setText(const std::string &);
    void setMaxWidth(unsigned int);
    void setPassword(bool);
    void onFocusChanged() override;

private:
    void removeLastCharacter();

    mutable std::string text;
    int x_, y_;
    bool password_;
    int displayCursor_;
    unsigned int maxWidth = 999;
};

#endif // RYAN_TEACHING_WINTER_SESSION_INPUT_H
