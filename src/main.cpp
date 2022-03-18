#include "StartPanel.h"
#include <jngl/all.hpp>
#include <jngl/init.hpp>
#include <filesystem>

class QuitWithEscape : public jngl::Job {
public:
    void step() override {
        if (jngl::keyPressed(jngl::key::Escape)) {
            jngl::quit();
        }
    }
    void draw() const override {}
};

std::function<std::shared_ptr<jngl::Work>()> jnglInit(jngl::AppParameters &params) {
#ifdef NDEBUG
    try {
#endif
        params.displayName = "撅 仙 贝 罢";
        params.screenSize = {720, 1280};
        return []() {
            chdir("image");
            jngl::setFont("Tiejili.ttf");
            jngl::setAntiAliasing(true);
            jngl::setIcon("ClickBefore");
            jngl::setFontSize(jngl::getScaleFactor() * 13);
            return std::make_shared<StartPanel>();
        };
#ifdef NDEBUG
    } catch (std::exception &e) {
        jngl::errorMessage(e.what());
        return {};
    }
#endif
}
