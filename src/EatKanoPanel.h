//
// Created by yiwei yang on 2/5/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_EATKANOPANEL_H
#define RYAN_TEACHING_WINTER_SESSION_EATKANOPANEL_H

#include "engine/Work.h"
#include <jngl/all.hpp>

class EatKanoPanel : public Work {
public:
    enum Mode {
        NORMAL, ENDLESS, PRACTICE
    };

    EatKanoPanel(const Mode type);

    ~EatKanoPanel() {}

    virtual void step();

    virtual void draw() const;

    int calRand() {
        return rand() % 4;
    }

    void Render() {}

    void DrawTime(const int x, const int y);

    int calCPS() { return 0; }

    Mode getType() const;

    double getTime() const;

    bool gameOver() const;

    void onQuitEvent();

    void DrawTime(const int x, const int y) const;

private:
    char keys_[4] = {'a', 's', 'd', 'f'};
    int current_panel[3][3];
    Mode type_;
};


#endif //RYAN_TEACHING_WINTER_SESSION_GAME_H
