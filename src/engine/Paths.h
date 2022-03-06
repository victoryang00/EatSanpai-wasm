#pragma once

#include "Singleton.hpp"

#include <string>

class Paths : public Singleton<Paths> {
public:
    Paths();
    std::string getData() const;

    std::string getGraphics();
    void setGraphics(const std::string &);

    std::string getPrefix();

    std::string getConfig();

    void setOriginalGfx(const std::string &);

private:
    std::string prefix;
    std::string configPath;
    std::string graphics = "./image/";
    std::string originalGfx;
};

Paths &getPaths();
