//
// Created by yiwei yang on 2/12/22.
//

#include "Scores.h"
#include "engine/Paths.h"
#include "engine/Screen.h"

#include <fstream>
#include <stdexcept>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <jngl/all.hpp>

Data::Data() : score(0), time(0) {
}

Highscore::Highscore(EatKanoPanel::Mode type) : type_(type), blink_(nullptr) {
    switch (type) {
        case EatKanoPanel::Mode::NORMAL:
            filename_ = getPaths().getConfig() + "normal.txt";
            break;
        case EatKanoPanel::Mode::ENDLESS:
            filename_ = getPaths().getConfig() + "endless.txt";
            break;
        case EatKanoPanel::Mode::PRACTICE:
            filename_ = getPaths().getConfig() + "practice.txt";
            break;
    }
    std::ifstream fin(filename_);
    if (fin) {
        for (int i = 0; i < 5; ++i) {
            Data temp;
            std::getline(fin, temp.name);
            fin >> (temp.score) >> (temp.time);
            highscores_.push_back(temp);
            fin.ignore(3, '\n'); // Read till next \n
        }
    } else {
        for (int i = 0; i < 5; ++i) {
            Data temp;
            temp.name = "Jan-Nik";
            temp.score = 0;
            temp.time = 13 * 60 + 37;
            highscores_.push_back(temp);
        }
    }
}

void Highscore::draw() const {
    assert(highscores_.size() == 5);
    jngl::pushMatrix();
    jngl::setFontSize(50);
    auto end = highscores_.end();
    int n = 1;
    bool foundEntryToBlink = false;
    for (auto it = highscores_.begin(); it != end; ++it) {
        std::string score;
        if (type_ == EatKanoPanel::Mode::NORMAL) {
            score = std::to_string(it->score);
        } else {
            int minutes = int(it->time / 60);
            int seconds = int(it->time - minutes * 60);
            int tenthOfASecond = int((it->time - seconds - minutes * 60) * 10);
            std::stringstream sstream;
            sstream.fill('0');
            sstream << minutes << ":" << std::setw(2) << seconds << "." << tenthOfASecond;
            score = sstream.str();
        }
        jngl::setFontColor(0, 0, 0);
        if (!foundEntryToBlink && blink_) {
            Data a = *blink_;
            Data b = *it;
            if (a == b) {
                foundEntryToBlink = true;
                int alpha = int(jngl::getTime() * 300) % 510;
                jngl::setFontColor(0, 0, 0, alpha > 255 ? 510 - alpha : alpha);
            }
        }
        jngl::print(score, 700 - static_cast<int>(jngl::getTextWidth(score)), 0);
        jngl::print(std::to_string(n) + ". " + it->name, 0, 0);
        jngl::translate(0, 80);
        ++n;
    }
    jngl::popMatrix();
}

void Highscore::Add(Data data) {
    highscores_.push_back(data);
    if (type_ == EatKanoPanel::Mode::NORMAL) {
        highscores_.sort([](const Data &lhs, const Data &rhs) {
            return lhs.score > rhs.score;
        });
    } else {
        highscores_.sort([](const Data &lhs, const Data &rhs) {
            return lhs.time < rhs.time;
        });
    }
    highscores_.pop_back();
}

bool Highscore::isHighscore(Data data) const {
    if (type_ == EatKanoPanel::Mode::NORMAL) {
        return data.score > highscores_.back().score;
    } else {
        return data.time < highscores_.back().time;
    }
}

void Highscore::save() const {
    std::ofstream fout(filename_);
    auto end = highscores_.end();
    for (auto it = highscores_.begin(); it != end; ++it) {
        fout << it->name << std::endl << it->score << " " << it->time << std::endl;
    }
}

void Highscore::Blink(Data d) {
    blink_.reset(new Data(d));
}
