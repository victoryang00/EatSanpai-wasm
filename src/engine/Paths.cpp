#include "Paths.h"
#include "Options.h"

#ifdef _WIN32
#include <shlobj.h>
#include <windows.h>
#endif
#include <filesystem>
#include <iostream>
#include <sstream>
namespace fs = std::filesystem;
#include <jngl.hpp>

#ifndef __IPHONE_OS_VERSION_MIN_REQUIRED
Paths::Paths() {
#if defined(__linux__)
    fs::current_path(fs::path(jngl::getBinaryPath()) / fs::path(".."));

    std::stringstream path;
    path << getenv("HOME") << "/.config/" << programDisplayName << "/";
    configPath = path.str();
#elif defined(__APPLE__)
    fs::current_path(fs::path(jngl::getBinaryPath()) / fs::path(".."));
    configPath = jngl::getConfigPath();
#elif defined(__EMSCRIPTEN__)
    configPath = std::string(getenv("HOME")) + "/.config/" + getOptions().title_ + "/";
#else
    const auto findDataDirectory = []() {
        fs::path binaryPath(jngl::getBinaryPath());
        fs::current_path(binaryPath);
        for (size_t i = 0; i < 3; ++i) {
            for (auto &p : fs::directory_iterator(".")) {
                const auto tmp = p.path().filename();
                if (tmp == "data") {
                    return;
                }
            }
            fs::current_path(fs::path(".."));
        }
    };
    findDataDirectory();

    TCHAR szPath[MAX_PATH];
    if (!SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, szPath))) {
        throw std::runtime_error("Couldn't get %AppData% location!");
    }
    std::stringstream path;
    path << szPath << "/" << programDisplayName << "/";
    configPath = path.str();
#endif
    fs::create_directory(configPath);
#else
Paths::Paths() : configPath(jngl::getConfigPath()) {
#endif
}

std::string Paths::getGraphics() { return graphics; }

void Paths::setGraphics(const std::string &g) { graphics = g; }

std::string Paths::getData() const {
#ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
    return "";
#else
    return prefix + "data/";
#endif
}

std::string Paths::getConfig() { return configPath; }

std::string Paths::getPrefix() { return prefix; }

void Paths::setOriginalGfx(const std::string &o) { originalGfx = o; }

Paths &getPaths() { return *Paths::handle(); }
