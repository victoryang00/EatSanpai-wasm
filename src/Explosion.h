//
// Created by yiwei yang on 3/13/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_EXPLOSION_H
#define RYAN_TEACHING_WINTER_SESSION_EXPLOSION_H

#include <jngl/all.hpp>

class Explosion {
public:
    Explosion(int x,int y, std::string location);
    void Step();
    void Draw() const;
    [[nodiscard]] bool isFinished() const;

private:
    int x_, y_;
    int countdown_;
    std::string location_;
    jngl::Sprite sprite;
};

#endif // RYAN_TEACHING_WINTER_SESSION_EXPLOSION_H
