//
// Created by yiwei yang on 2/13/22.
//

#include "GameOverPanel.h"
#include "StartPanel.h"
#include "engine/Fade.h"
#include "engine/Options.h"

#include <utility>

extern bool clicked_wrong;

GameOverPanel::GameOverPanel(EatKanoPanel::Mode mode_, const Data &data, HighScore highscore_)
    : data_(data), highscore_(std::move(highscore_)), restart_(new ButtonBox(0, 0)) {
    data_ = data;
    if (highscore_.isHighscore(data_)) {
        highscore_.Add(data_);
        highscore_.save();
        if (mode_ == EatKanoPanel::ENDLESS)
            getOptions().endlessHighscore_ = highscore_;
        else if (mode_ == EatKanoPanel::NORMAL)
            getOptions().normalHighscore_ = highscore_;
    }
    restart_->add("Back", [this, &mode_] { OnBack(mode_); });
    restart_->add("Quit", [this] { onQuitEvent(); });
    addWidget(restart_);
}

void GameOverPanel::step() { StepWidgets(); }

void GameOverPanel::draw() const {
    DrawWidgets();
    jngl::print("Game Over", -220, -400);
    jngl::print("Highest Score:", -280, -350);
    jngl::print(std::to_string(data_.score), -50, -350);
}

void GameOverPanel::onQuitEvent() { Work::onQuitEvent(); }

void GameOverPanel::BlinkHighscore(Data data) {
    highscore_.Blink(std::move(data));
    jngl::setFontSize(60);
    jngl::setFontColor(255, 255, 0);
    jngl::print(std::to_string(data_.score), -200, -400);
}
void GameOverPanel::OnBack(EatKanoPanel::Mode mode_) const {
    clicked_wrong = false;
    jngl::setSpriteAlpha(255);
    jngl::setWork(std::make_shared<Fade>(std::make_shared<EatKanoPanel>(mode_)));
}