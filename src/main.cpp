#include <jngl.hpp>

JNGL_MAIN_BEGIN
    {
        jngl::showWindow("吃掉小鹿乃", 800, 600);
        while (jngl::running()) {
            jngl::updateInput();
            jngl::print("Hello World!", -100, -10);
            jngl::swapBuffers();
        }
    }JNGL_MAIN_END