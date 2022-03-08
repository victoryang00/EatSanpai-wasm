//
// Created by yiwei yang on 2/13/22.
//

#include "GameOverPanel.h"
#include "engine/Options.h"

#include <utility>

GameOverPanel::GameOverPanel(EatKanoPanel::Mode mode_,const Data &data, Highscore highscore_)
    : data_(data), highscore_(std::move(highscore_)), restart_(new ButtonBox(300, 100)) {
    data_ = data;
    if (highscore_.isHighscore(data_)) {
        highscore_.Add(data_);
        highscore_.save();
        if (mode_ == EatKanoPanel::ENDLESS)
            getOptions().endlessHighscore_= highscore_;
        else if (mode_ == EatKanoPanel::NORMAL)
            getOptions().normalHighscore_ = highscore_;
    }
}

void GameOverPanel::step() {}

void GameOverPanel::draw() const {}

void GameOverPanel::onQuitEvent() { Work::onQuitEvent(); }

void GameOverPanel::BlinkHighscore(Data data) {
    highscore_.Blink(std::move(data));
    jngl::setFontSize(60);
    jngl::setFontColor(255, 255, 0);
    jngl::print(std::to_string(data_.score), -250, -420);
}