#pragma once

//#include <memory>
#include <jngl/work.hpp>
#include <vector>

class Widget;

class Work : public jngl::Work {
public:
    virtual void step() = 0;
    virtual void draw() const = 0;
    virtual ~Work();
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
