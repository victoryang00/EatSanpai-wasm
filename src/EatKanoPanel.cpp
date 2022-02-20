//
// Created by yiwei yang on 2/5/22.
//

#include "EatKanoPanel.h"

#include "engine/Screen.h"
#include "engine/Procedure.h"
#include "GameOverPanel.h"

#include <sstream>
#include <iomanip>
#include <boost/lexical_cast.hpp>

EatKanoPanel::EatKanoPanel(const Mode type )
        : type_(type) {
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
    if (jngl::getTime() > 1) { // Don't allow pausing the game more then one time per second
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

void EatKanoPanel::draw() const {
//    jngl::pushMatrix();
//    jngl::rotate(rotateDegree_);
//    jngl::scale(1 + rotateDegree_ / 270);
//
//    field_.draw();
//    if (!rotateScreen_) {
//        jngl::setFontColor(0, 0, 0);
//        jngl::setFontSize(60);
//        jngl::pushMatrix();
//        jngl::translate(-600, oldNextPosition_);
//        field_.drawNextTetromino();
//        jngl::popMatrix();
//        if (type_ == GameType::FIFTYLINES) {
//            DrawTime(450, -500);
//        } else {
//            jngl::print("Score: ", 450, -500);
//            jngl::print(std::to_string(field_.GetScore()), 450, -400);
//            DrawTime(450, 220);
//        }
//        jngl::print("Level: ", 450, -260);
//        jngl::print(std::to_string(field_.GetLevel()), 450, -160);
//        jngl::print("Lines: ", 450, -20);
//        jngl::print(std::to_string(field_.GetLines()), 450, 80);
//    }
//    jngl::popMatrix();
}

double EatKanoPanel::getTime() const {
    return 0.0f;
}


EatKanoPanel::Mode EatKanoPanel::getType() const {
    return type_;
}

bool EatKanoPanel::gameOver() const {
    return false;
}