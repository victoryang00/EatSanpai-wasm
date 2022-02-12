//
// Created by yiwei yang on 2/5/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_STARTPANEL_H
#define RYAN_TEACHING_WINTER_SESSION_STARTPANEL_H


#include "engine/Work.h"
#include "ButtonBox.h"
#include "Scores.h"
#include "jngl/Finally.hpp"
#include <functional>

class StartPanel : public Work {
public:
    StartPanel();
    virtual void step();
    virtual void draw() const;

    void BlinkHighscore(Data);

    void isNewGame() const;
    void startGame() const;
    void OptionsMenuCallback() const;
    void QuitGame() const;
private:
    std::shared_ptr<ButtonBox> buttonBox_;
    Highscore normalHighscore_;
    Highscore fiftyLinesHighscore_;
};


#endif //RYAN_TEACHING_WINTER_SESSION_START_H
