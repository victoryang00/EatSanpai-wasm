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
    for (int & i : curr_panel) {
        auto rand_int = calRand();
        i = rand_int;
    }
    for (int i = 0; i < 3; i++) {
        this->keys_[i] = getOptions().inputKey[i];
    }
}

void EatKanoPanel::draw() const {
    GetScreen().DrawCentered("./image/board.png", 0, 0);
    GetScreen().DrawCentered(getOptions().postimg, 0, 0);

    if (getType() == Mode::NORMAL) {
        DrawTime(100, 300);
    } else if (getType() == Mode::ENDLESS) {
        DrawCPS();
    }
}
void EatKanoPanel::step() {
    //    StepToRotateScreen();
    /** To determine the game over or not */
    //    if (field_.GameOver()) {
    /** Show the music and blink */
    //        pauseTime_ = jngl::getTime();
    //        jngl::setWork(std::make_shared<GameOverScreen>(this));
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
    double time = getTime();
    int minutes = int(time / 60);
    int seconds = int(time - minutes * 60);
    std::stringstream sstream;
    sstream.fill('0');
    sstream << minutes << ":" << std::setw(2) << seconds;
    jngl::print(sstream.str(), 450, y + 100);
}

double EatKanoPanel::getTime() { return 0.0f; }

EatKanoPanel::Mode EatKanoPanel::getType() const { return type_; }

bool EatKanoPanel::gameOver() const {
    if (getTime() < 0.0001 || clicked_wrong) {
        return true;
    }
    return false;
}

void EatKanoPanel::DrawCPS() const {
    jngl::print("CPS: ", 100, 300);
    std::stringstream sstream;
    sstream << std::fixed << std::setprecision(2) << calCPS();
    jngl::print(sstream.str(), 450, 300);
}
