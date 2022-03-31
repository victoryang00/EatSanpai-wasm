//
// Created by yiwei yang on 2/5/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_STARTPANEL_H
#define RYAN_TEACHING_WINTER_SESSION_STARTPANEL_H

#include "ButtonBox.h"
#include "Scores.h"
#include "engine/Work.h"
#include <functional>

class StartPanel : public Work {
public:
    StartPanel();
    void step() override;
    void draw() const override;

    void Normal() const;
    void Endless() const;
    void Practice() const;
    void OptionsMenuCallback() const;

private:
    std::shared_ptr<ButtonBox> buttonBox_;
};

#endif // RYAN_TEACHING_WINTER_SESSION_STARTPANEL_H
