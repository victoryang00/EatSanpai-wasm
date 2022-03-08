#pragma once

#include "Singleton.hpp"
#include "Vector2D.h"

#include <jngl/Vec2.hpp>
#include <string>

class Screen : public Singleton<Screen> {
public:
    void DrawCentered(const std::string &filename, double x, double y);
    void DrawCentered(const std::string &filename, const Vector2d &position);
    void printCentered(const std::string &text, jngl::Vec2);
};

Screen &GetScreen();
