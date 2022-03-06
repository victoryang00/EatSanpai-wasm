//
// Created by yiwei yang on 2/13/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_OPTIONSMENU_H
#define RYAN_TEACHING_WINTER_SESSION_OPTIONSMENU_H

#include "engine/Work.h"
#include "Chooser.h"
#include "Input.h"

#include <vector>

class Button;

class OptionsMenu : public Work {
public:
    OptionsMenu();
    void step();
    void draw() const;
    void OnBack() const;

private:
    std::shared_ptr<Input> select_preimg_;
    std::shared_ptr<Input> select_postimg_;
    std::shared_ptr<Input> input_;
    std::shared_ptr<Input> headline_;
    std::shared_ptr<Button> back_;
};



#endif //RYAN_TEACHING_WINTER_SESSION_OPTIONSMENU_H
