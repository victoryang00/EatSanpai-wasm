//
// Created by yiwei yang on 2/5/22.
//

#include "StartPanel.h"

#include "ButtonBox.h"
#include "EatKanoPanel.h"
#include "OptionsMenu.h"
#include "engine/Fade.h"
#include "engine/Paths.h"
#include "engine/Procedure.h"
#include "engine/Screen.h"

#include <ctime>
#include <jngl/all.hpp>

StartPanel::StartPanel()
    : buttonBox_(new ButtonBox(0, 0)), normalHighscore_(EatKanoPanel::Mode::NORMAL),
      endlessHighscore_(EatKanoPanel::Mode::ENDLESS) {

    buttonBox_->add("Normal", std::bind(&StartPanel::Normal, this));
    buttonBox_->add("Endless", std::bind(&StartPanel::Endless, this));
    buttonBox_->add("Practice", std::bind(&StartPanel::Practice, this));
    buttonBox_->add("Options", std::bind(&StartPanel::OptionsMenuCallback, this));
    buttonBox_->add("Quit", std::bind(&StartPanel::QuitGame, this));
    addWidget(buttonBox_);

}

void StartPanel::BlinkHighscore(Data data) {
    normalHighscore_.Blink(data);
    endlessHighscore_.Blink(data);
}

void StartPanel::step() { StepWidgets(); }

void StartPanel::draw() const {
    jngl::setBackgroundColor(0xffffff_rgb);
    GetScreen().DrawCentered("./image/background.png", 200, 0);

    DrawWidgets();

    jngl::pushMatrix();
    jngl::translate(0, 0);
    jngl::setFontSize(30);
    jngl::setFontColor(255, 255, 0);
    jngl::print("迫真音游", 0, -30);
    jngl::setFontSize(20);
    jngl::setFontColor(0, 0, 0);
    jngl::print("从最底下仙贝的开始", 0, -50);
    jngl::print("看你20秒多少分", 0, -70);
//    normalHighscore_.draw();
//    jngl::translate(0, 530);
//    jngl::print("Highscores 50 Lines", 0, -90);
//    endlessHighscore_.draw();
    jngl::popMatrix();
}

void StartPanel::Normal() const { jngl::setWork(std::make_shared<Fade>(std::make_shared<EatKanoPanel>(mode_))); }
void StartPanel::Endless() const { jngl::setWork(std::make_shared<Fade>(std::make_shared<EatKanoPanel>(mode_))); }
void StartPanel::Practice() const { jngl::setWork(std::make_shared<Fade>(std::make_shared<EatKanoPanel>(mode_))); }

void StartPanel::OptionsMenuCallback() const { jngl::setWork(std::make_shared<Fade>(std::make_shared<OptionsMenu>())); }

void StartPanel::QuitGame() const { jngl::quit(); }