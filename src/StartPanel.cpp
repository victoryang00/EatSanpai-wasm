//
// Created by yiwei yang on 2/5/22.
//

#include "StartPanel.h"

#include "ButtonBox.h"
#include "EatKanoPanel.h"
#include "OptionsMenu.h"
#include "engine/Fade.h"
#include "engine/Options.h"
#include "engine/Screen.h"

#include <jngl/all.hpp>

StartPanel::StartPanel() : buttonBox_(new ButtonBox(0, 200)){
    buttonBox_->add("Normal", [this] { Normal(); });
    buttonBox_->add("Endless", [this] { Endless(); });
    buttonBox_->add("Practice", [this] { Practice(); });
    buttonBox_->add("Options", [this] { OptionsMenuCallback(); });
    addWidget(buttonBox_);
}

void StartPanel::step() { StepWidgets(); }

void StartPanel::draw() const {
    jngl::setBackgroundColor(0xffffff_rgb);
    GetScreen().DrawCentered("background", 0, 0);
    DrawWidgets();

    jngl::pushMatrix();
    jngl::translate(0, 0);
    jngl::setFontSize(60);
    jngl::setFontColor(255, 255, 0);
    jngl::print("迫真音游", -250, -420);
    jngl::setFontSize(50);
    jngl::setFontColor(255, 255, 255);
    jngl::print("从最底下仙贝的开始", -250, -350);
    jngl::print("看你20秒多少分", -250, -300);
    jngl::popMatrix();
}

void StartPanel::Normal() const { jngl::setWork(std::make_shared<Fade>(std::make_shared<EatKanoPanel>(EatKanoPanel::Mode::NORMAL))); }
void StartPanel::Endless() const { jngl::setWork(std::make_shared<Fade>(std::make_shared<EatKanoPanel>(EatKanoPanel::Mode::ENDLESS))); }
void StartPanel::Practice() const { jngl::setWork(std::make_shared<Fade>(std::make_shared<EatKanoPanel>(EatKanoPanel::Mode::PRACTICE))); }

void StartPanel::OptionsMenuCallback() const { jngl::setWork(std::make_shared<Fade>(std::make_shared<OptionsMenu>())); }
