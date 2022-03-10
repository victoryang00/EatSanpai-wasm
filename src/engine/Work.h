#pragma once

#include <jngl/work.hpp>
#include <vector>

class Widget;

class Work : public jngl::Work {
public:
    void step() override = 0;
    void draw() const override = 0;
    ~Work() override;
    void StepWidgets();
    void DrawWidgets() const;
    void addWidget(const std::shared_ptr<Widget> &);
    void FocusNext();
    void FocusPrevious();

protected:
    void StepFocus();
    std::vector<std::shared_ptr<Widget>> widgets_;
    std::shared_ptr<Widget> focusedWidget_;
};
