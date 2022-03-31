//
// Created by yiwei yang on 2/13/22.
//

#include "OptionsMenu.h"
#include "ButtonBox.h"
#include "StartPanel.h"
#include "engine/Fade.h"
#include "engine/Options.h"
#include "engine/Screen.h"

#include <jngl/all.hpp>
#include <memory>

OptionsMenu::OptionsMenu()
    : select_preimg_(new Input(-200, -450)), select_postimg_(new Input(-200, -300)), input_(new Input(-200, -150)),
      headline_(new Input(-200, 0)) {
    back_ = std::make_shared<Button>("Back", [this] { OnBack(); });
    back_->setCenter(0, 400);
    addWidget(select_preimg_);
    addWidget(select_postimg_);
    addWidget(input_);
    addWidget(headline_);
    addWidget(back_);
}

void OptionsMenu::step() { StepWidgets(); }

void OptionsMenu::draw() const {
    GetScreen().DrawCentered("background", 0, 0);
    DrawWidgets();
    jngl::setFontColor(255, 255, 255);
    jngl::setFontSize(40);
    GetScreen().printCentered("设置点击前的图", {0, -500});
    GetScreen().printCentered("设置点击后的图", {0, -350});
    GetScreen().printCentered("标题", {0, -50});
    GetScreen().printCentered("按键", {0, -200});
}

void OptionsMenu::OnBack() const {
    getOptions().inputKey = input_->getText();
    getOptions().preimg = select_preimg_->getText();
    getOptions().postimg = select_postimg_->getText();
    getOptions().title_ = headline_->getText();
    getOptions().Save();
    jngl::setWork(std::make_shared<Fade>(std::make_shared<StartPanel>()));
}
