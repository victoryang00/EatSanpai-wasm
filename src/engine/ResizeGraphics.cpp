#include "ResizeGraphics.h"
#include "Options.h"
#include "Paths.h"
#include "Screen.h"

#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <jngl.hpp>

void ScanPath(fs::path path, std::deque<std::string> &filesToResize) {
    fs::directory_iterator end;
    for (fs::directory_iterator it(path); it != end; ++it) {
        if (fs::is_directory(it->status())) {
            ScanPath(it->path(), filesToResize);
        } else {
            std::string file = it->path().string();
            const std::string extension = ".webp";
            if (file.substr(file.size() - extension.size()) == extension) {
                filesToResize.push_back(std::string(it->path().string()).erase(0, jngl::getPrefix().size()));
            }
        }
    }
}

ResizeGraphics::ResizeGraphics() : originalSize_(-1) {
    fs::path path(jngl::getPrefix() + getPaths().getData() + "gfx");
    fs::directory_iterator end;
    for (fs::directory_iterator it(path); it != end; ++it) {
        if (fs::is_directory(it->status())) {
            std::string name = it->path().string();
            try {
                auto tmp = boost::lexical_cast<int>(name.substr(name.rfind('x') + 1));
                if (tmp > originalSize_) {
                    originalSize_ = tmp;
                    jngl::debug("Original screen height: ");
                    jngl::debugLn(originalSize_);
                }
            } catch (boost::bad_lexical_cast &) {
                // Bad cast, this doesn't seem to be the right directory
            }
        }
    }

    const std::string origGfx = getPaths().getData() + "gfx/x" + std::to_string(originalSize_) + "/";
    getPaths().setOriginalGfx(origGfx);
    jngl::setScaleFactor(double(jngl::getWindowHeight()) / double(originalSize_));
    getPaths().setGraphics(origGfx);
    ScanPath(jngl::getPrefix() + getPaths().getData() + "gfx/x" + std::to_string(originalSize_), filesToResize_);
}

ResizeGraphics::~ResizeGraphics() = default;

bool ResizeGraphics::isFinished(float &percentage) {
    if (filesToResize_.empty()) {
        return true;
    }

    static size_t numberOfImages = filesToResize_.size();
    percentage = float(100 - filesToResize_.size() * 100 / numberOfImages);

    // Don't do anything in the first frame in order to draw the loading screen for the first time
    static bool firstFrame = true;
    if (firstFrame) {
        firstFrame = false;
        return false;
    }

    std::string basedir = getPaths().getData() + std::to_string(originalSize_);
    std::string relativeFilename(filesToResize_[0].substr(basedir.size() + 1));
    std::string newFilename = getPaths().getGraphics() + relativeFilename;

    jngl::load(newFilename.substr(0, newFilename.size() - 5));
    filesToResize_.pop_front();
    return false;
}
