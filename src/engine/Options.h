#pragma once

#include "Singleton.hpp"
#include "../Scores.h"

#include <cereal/cereal.hpp>

class Options : public Singleton<Options> {
public:
    Options();
    void Save() const;

    int windowWidth = 720;
    int windowHeight = 1280;
    bool fullscreen = false;
    std::string inputKey = "asdf";
    std::string postimg = "./image/ClickBefore.png";
    std::string preimg = "./image/AfterClicking.png";
    Highscore endlessHighscore_;
    Highscore normalHighscore_;

private:
    std::string filename;

    friend class cereal::access;
    template <class Archive> void serialize(Archive &ar) {
        ar &CEREAL_NVP(windowWidth);
        ar &CEREAL_NVP(windowHeight);
        ar &CEREAL_NVP(fullscreen);
        ar &CEREAL_NVP(inputKey);
    }
};

Options &getOptions(); // Easier access to the singleton
