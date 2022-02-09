#include <jngl.hpp>

JNGL_MAIN_BEGIN
    {
        jngl::showWindow("EatKano", 400, 800);
        while (jngl::running()) {
            jngl::updateInput();
            jngl::swapBuffers();
        }
    }JNGL_MAIN_END