//
// Created by yiwei yang on 2/5/22.
//

#include "EatKanoPanel.h"

#include "GameOverPanel.h"
#include "engine/Options.h"
#include "engine/Procedure.h"
#include "engine/Screen.h"

#include <boost/lexical_cast.hpp>
#include <iomanip>
#include <sstream>

EatKanoPanel::EatKanoPanel(const Mode type) : type_(type) {
    int j = 0;
    for (auto &&i : getOptions().inputKey) {
        keys_[j] = i;
        j++;
    }
    for (int &i : curr_panel) {
        auto rand_int = calRand();
        i = rand_int;
    }
    for (int i = 0; i < 3; i++) {
        this->keys_[i] = getOptions().inputKey[i];
    }
}

void EatKanoPanel::draw() const {
    int j = 0;
    GetScreen().DrawCentered("./image/board.png", 0, 0);
    for (auto &i : curr_panel) {
        GetScreen().DrawCentered(getOptions().preimg, std::get<0>(map_[j][i]), std::get<1>(map_[j][i]));
        j++;
    }
    if (getType() == Mode::NORMAL) {
        DrawTime(-200, -400);
    } else if (getType() == Mode::ENDLESS) {
        DrawCPS();
    }
}
void EatKanoPanel::step() {
    int j = 0;

    for (auto &inner_map_ : map_)
        for (auto &inner_map_2 : inner_map_) {
            check_box_.emplace_back(
                std::make_shared<HiddenButton>(HiddenButton([this] { UpdatePanel(); }, keys_[j % 4])));
            j++;
        }
    /** Draw the hidden box */
    for (auto &i : check_box_)
        addWidget(i);

    /** To determine the game over or not */
    if (gameOver()) {
        /** Show the music and blink */
        jngl::play("./music/end.ogg");
        std::__libcpp_thread_sleep_for(std::chrono::milliseconds(1000));
        jngl::play("./music/err.ogg");
        //        pauseTime_ = jngl::getTime();
        if (getType() == Mode::NORMAL) {
            jngl::setWork(std::make_shared<GameOverPanel>(type_, Data(), getOptions().normalHighscore_));
        } else if (getType() == Mode::ENDLESS) {
            jngl::setWork(std::make_shared<GameOverPanel>(type_, Data(), getOptions().endlessHighscore_));
        }
    }
    //    } else {
    //        field_.SetPause(false);
    //        field_.step();
    //        if (replayRecorder) {
    //            replayRecorder->Step();
    //        }
    //        if (type_ == GameType::FIFTYLINES && field_.GetLines() >= 50) {
    //            field_.setGameOver(true);
    //        }
    //    }
    //    nextPosition_ = field_.GetNextPosition();
    //    oldNextPosition_ = (nextPosition_ - oldNextPosition_) * 0.01 + oldNextPosition_;
    //    if (pauseTime_ > 0.0001 && !field_.GameOver()) {
    //        pauseTime_ = 0;
    //    }

    if (jngl::keyPressed('p') || jngl::keyPressed(jngl::key::Escape)) {
        onQuitEvent(); // Pause
    }
}

void EatKanoPanel::onQuitEvent() {
    if (jngl::getTime() > 0.0001) { // Don't allow pausing the game more then one time per second
        jngl::cancelQuit();
    }
}

void EatKanoPanel::DrawTime(const int x, const int y) const {
    jngl::print("Time: ", x, y);
    auto time = getTime();
    int minutes = int(time / 60);
    int seconds = int(time - minutes * 60);
    if (started_) {
        std::stringstream sstream;
        sstream.fill('0');
        sstream << seconds;
        jngl::print(sstream.str(), x + 300, y);
    } else {
        jngl::print("20", x + 300, y);
    }
}

long long EatKanoPanel::getTime() const {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time_).count();
}

EatKanoPanel::Mode EatKanoPanel::getType() const { return type_; }

bool EatKanoPanel::gameOver() const {
    if (getTime() < 0.0001 || clicked_wrong) {
        return true;
    }
    return false;
}

void EatKanoPanel::DrawCPS() const {
    jngl::print("CPS: ", 0, -200);
    std::stringstream sstream;
    sstream << std::fixed << std::setprecision(2) << calCPS();
    jngl::print(sstream.str(), 450, 300);
}

float EatKanoPanel::calCPS() const { return score / getTime(); }

void EatKanoPanel::UpdatePanel() {
    /** make the updated button clicked and check one by one, if not success blink, if success rerand */
    for (int &i : curr_panel) {
        auto rand_int = calRand();
        i = rand_int;
    }
    if (!started_) {
        started_ = true;
    }
    jngl::play("./music/tap.ogg");
}
