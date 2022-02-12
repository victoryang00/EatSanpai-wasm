#include "Procedure.h"
#include "Options.h"
#include "Screen.h"

#include <jngl/all.hpp>
#include <stdexcept>

Procedure::Procedure()
        : oldTime_(jngl::getTime()), needDraw_(true), fps_(0), fpsTemp_(0), changeWork_(false),
          running_(true), showFps_(false) {
}

Procedure &GetProcedure() {
    return *Procedure::handle();
}

const double Procedure::timePerStep_ = 1.0 / 100.0;
