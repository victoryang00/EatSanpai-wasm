//
// Created by yiwei yang on 2/13/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_GAMEOVERPANEL_H
#define RYAN_TEACHING_WINTER_SESSION_GAMEOVERPANEL_H

#include "Scores.h"
#include "engine/Work.h"
#include <jngl/Vec2.hpp>

class EatKanoPanel;

class GameOverPanel : public Work {
public:
    GameOverPanel(EatKanoPanel *);
    void step();
    void draw() const;
    void onQuitEvent();

private:
    bool isHighscore() const;
    EatKanoPanel *const game_;
    int blink_;
    Data data_;
    Highscore highscore_;
    std::shared_ptr<jngl::Work> work_;
};

#endif // RYAN_TEACHING_WINTER_SESSION_GAMEOVERPANEL_H
