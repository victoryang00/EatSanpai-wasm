//
// Created by yiwei yang on 3/13/22.
//

#include "Explosion.h"

#include "engine/Paths.h"
#include "engine/Screen.h"

#include <jngl.hpp>
#include <utility>

Explosion::Explosion(int x, int y, std::string location)
    : countdown_(255), location_(std::move(location)), sprite(getPaths().getGraphics() + location_), x_(x), y_(y) {}

void Explosion::Step() { countdown_ -= 5; }

bool Explosion::isFinished() const { return countdown_ < 0; }

void Explosion::Draw() const {
    jngl::setSpriteAlpha(countdown_);
    sprite.draw(jngl::modelview().translate({double(x_), double(y_)}));
    jngl::setSpriteAlpha(255);
}