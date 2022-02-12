#pragma once

#include "Work.h"

class Fade : public Work {
public:
    Fade(std::shared_ptr<Work>, int speed = 15);
    void step() override;
    void draw() const override;

private:
    std::shared_ptr<Work> work_;
    std::shared_ptr<jngl::Work> oldWork_;
    double fadeCount_;
    int speed_;
};
