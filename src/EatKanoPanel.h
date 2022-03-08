//
// Created by yiwei yang on 2/5/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_EATKANOPANEL_H
#define RYAN_TEACHING_WINTER_SESSION_EATKANOPANEL_H

#include "engine/Work.h"
#include <jngl/all.hpp>

class EatKanoPanel : public Work {
public:
    enum Mode { NORMAL, ENDLESS, PRACTICE };

    explicit EatKanoPanel(Mode type);

    ~EatKanoPanel() override = default;

    void step() override;

    void draw() const override;

    [[nodiscard]] static int calRand() { return std::rand() % 4; }

    [[nodiscard]] Mode getType() const;

    [[nodiscard]] bool gameOver() const;

    static int calCPS() { return 0; }

    static double getTime();

    void onQuitEvent() override;

    void DrawTime(int x, int y) const;

    void DrawCPS() const;

private:
    char keys_[4] = {'a', 's', 'd', 'f'};
    std::vector<std::vector<std::tuple<int, int>>> map_ = {
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}}, {{1, 0}, {1, 1}, {1, 2}, {1, 3}}, {{2, 0}, {2, 1}, {2, 2}, {2, 3}},
        {{2, 0}, {2, 1}, {2, 2}, {2, 3}}, {{2, 0}, {2, 1}, {2, 2}, {2, 3}}, {{3, 0}, {3, 1}, {3, 2}, {3, 3}}};
    int curr_panel[6] = {0, 0, 0, 0, 0, 0};
    Mode type_;
    bool clicked_wrong;
};

#endif // RYAN_TEACHING_WINTER_SESSION_GAME_H
