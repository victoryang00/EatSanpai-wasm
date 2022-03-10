//
// Created by yiwei yang on 2/5/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_EATKANOPANEL_H
#define RYAN_TEACHING_WINTER_SESSION_EATKANOPANEL_H

#include "ButtonBox.h"
#include "engine/Work.h"
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

    [[nodiscard]] long long getTime() const;

    void onQuitEvent() override;

    void DrawTime(int x, int y) const;

    void DrawCPS() const;

    void UpdatePanel();

private:
    char keys_[4] = {'a', 's', 'd', 'f'};
    std::vector<std::vector<std::tuple<int, int>>> map_ = {
        {{-260, -480}, {-80, -480}, {93, -480}, {270, -480}}, {{-260, -296}, {-80, -296}, {93, -296}, {270, -296}},
        {{-260, -112}, {-80, -112}, {93, -112}, {270, -112}}, {{-260, 72}, {-80, 72}, {93, 72}, {270, 72}},
        {{-260, 256}, {-80, 256}, {93, 256}, {270, 256}},     {{-260, 440}, {-80, 440}, {93, 440}, {270, 440}}};
    int curr_panel[6] = {0, 0, 0, 0, 0, 0};
    Mode type_;
    std::vector<std::shared_ptr<HiddenButton>> check_box_;
    std::vector<std::shared_ptr<SenPai>> widgets_;
    std::chrono::steady_clock::time_point start_time_ = std::chrono::steady_clock::now();
    bool clicked_wrong = false;
    bool started_ = false;
    int score;
};

#endif // RYAN_TEACHING_WINTER_SESSION_EATKANOPANEL_H
