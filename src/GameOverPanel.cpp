//
// Created by yiwei yang on 2/13/22.
//

#include "GameOverPanel.h"

#include <utility>

GameOverPanel::GameOverPanel(const Data &data, Highscore highscore_)
    : data_(data), highscore_(std::move(highscore_)), restart_(new ButtonBox(300, 100)) {
    data_ = data;
    highscore_.isHighscore(data_);
    //    if (data_.get_score() > highscore_.get_score()) {
    //        highscore_.set_score(data_.get_score());
    //        highscore_.set_name(data_.get_name());
    //    }
    //    highscore_.save();
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