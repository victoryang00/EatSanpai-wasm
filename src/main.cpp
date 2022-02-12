#include "StartPanel.h"
#include <jngl/all.hpp>
#include <jngl/init.hpp>

class QuitWithEscape : public jngl::Job {
public:
    void step() override {
        if (jngl::keyPressed(jngl::key::Escape)) {
            jngl::quit();
        }
    }

    void draw() const override {
    }
};

std::function<std::shared_ptr<jngl::Work>()> jnglInit(jngl::AppParameters& params) {
#ifdef NDEBUG
    try {
#endif
    params.displayName = "EatKano";
    params.screenSize = { 1280, 720 };
    return []() {
        jngl::setAntiAliasing(true);
        jngl::setIcon("../image/ClickBefore.png");
        jngl::setFontSize(jngl::getScaleFactor() * 13);
        return std::make_shared<StartPanel>();
    };
#ifdef NDEBUG
    } catch (std::exception& e) {
        jngl::errorMessage(e.what());
        return false;
    }
#endif
}
