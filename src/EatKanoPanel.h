//
// Created by yiwei yang on 2/5/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_EATKANOPANEL_H
#define RYAN_TEACHING_WINTER_SESSION_EATKANOPANEL_H

#include "engine/Work.h"
#include <jngl/Vec2.hpp>

class EatKanoPanel : public Work{
public:
    enum Mode {
        NORMAL, ENDLESS, PRACTICE
    };

    EatKanoPanel() {}
    ~EatKanoPanel() {}

    virtual void step();
    virtual void draw() const;
    int calRand() {
        return rand() % 4;
    }

    void Render() {}

    int calCPS() { return 0; }

private:
    int random_key;
    int current_panel[3][3];
};


#endif //RYAN_TEACHING_WINTER_SESSION_GAME_H
