#include "DebugOverlay.h"

#include <cmath>
#include <jngl/all.hpp>

DebugOverlay::DebugOverlay() {
    fps.setTop(1);
    fps.setLeft(0);
}

void DebugOverlay::step() {
    if (jngl::keyPressed(jngl::key::F1)) {
        visible = !visible;
    }
    if (visible) {
        fpsTemp += jngl::getFPS();
        ++fpsCounter;
        if (fpsCounter == 10) {
            fps.setText(std::string("FPS: ") + std::to_string(std::lround(fpsTemp / fpsCounter)));
            fpsCounter = 0;
            fpsTemp = 0;
        }
    }
}

void DebugOverlay::draw() const {
    if (visible) {
        jngl::setColor(100, 255, 100, 200);
        jngl::drawRect(-jngl::getScreenSize() / 2.0, {fps.getWidth() + 5, fps.getHeight()});
        jngl::setFontColor(0, 0, 0, 200);
        fps.draw();
    }
}
