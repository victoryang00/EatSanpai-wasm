//
// Created by yiwei yang on 2/5/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_EATKANOPANEL_H
#define RYAN_TEACHING_WINTER_SESSION_EATKANOPANEL_H

#include "engine/Work.h"
#include "ButtonBox.h"
#include <iostream>
#include <jngl/all.hpp>
#include <random>

class EatKanoPanel : public Work {
public:
    enum Mode { NORMAL, ENDLESS, PRACTICE };

    explicit EatKanoPanel(Mode type);

    ~EatKanoPanel() override = default;

    void step() override;

    void draw() const override;

    [[nodiscard]] static int calRand() {
        std::mt19937 mt;
        std::random_device rnd;
        mt.seed(rnd());
        return mt() % 4;
    }

    [[nodiscard]] Mode getType() const;

    [[nodiscard]] bool gameOver() const;

    [[nodiscard]] float calCPS() const;

    [[nodiscard]] double getTime() const;

    void onQuitEvent() override;

    void DrawTime(int x, int y) const;

    void DrawCPS() const;

    void UpdatePanel();

private:
    char keys_[4] = {'a', 's', 'd', 'f'};
    std::vector<std::vector<std::tuple<int, int>>> map_ = {
        {{-320, -520}, {-143, -520}, {33, -520}, {220, -520}}, {{-320, -336}, {-143, -336}, {33, -336}, {210, -336}},
        {{-320, -152}, {-143, -152}, {33, -152}, {210, -152}}, {{-320, 32}, {-143, 32}, {33, 32}, {210, 32}},
        {{-320, 216}, {-143, 216}, {33, 216}, {210, 216}},     {{-320, 400}, {-143, 400}, {33, 400}, {210, 400}}};
    int curr_panel[6] = {0, 0, 0, 0, 0, 0};
    Mode type_;
    std::vector<std::shared_ptr<HiddenButton>> check_box_;
    std::chrono::steady_clock::time_point start_time_ = std::chrono::steady_clock::now();
    bool clicked_wrong = false;
    bool started_ = false;
    int score;
};

#endif // RYAN_TEACHING_WINTER_SESSION_EATKANOPANEL_H
