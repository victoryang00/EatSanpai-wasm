#pragma once

#include <deque>

#include <filesystem>
namespace fs = std::filesystem;

class ResizeGraphics {
public:
    ResizeGraphics();
    ~ResizeGraphics();
    bool isFinished(float &percentage);

private:
    std::deque<std::string> filesToResize_;
    int originalSize_;
};

void ScanPath(fs::path path, std::deque<std::string> &filesToResize);
