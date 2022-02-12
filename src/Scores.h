//
// Created by yiwei yang on 2/12/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_SCORES_H
#define RYAN_TEACHING_WINTER_SESSION_SCORES_H

#include <list>
#include <string>
#include <boost/shared_ptr.hpp>
#include "EatKanoPanel.h"
#include <compare>

struct Data {
    Data();
    int score;
    double time;
    std::string name;
    auto operator<=>(const Data& rhs) const = default;
};

class Highscore {
public:
    Highscore(EatKanoPanel::Mode type);
    bool isHighscore(Data data) const;
    void draw() const;
    void Add(Data);
    void save() const;
    void Blink(Data);
private:
    std::list<Data> highscores_;
    EatKanoPanel::Mode type_;
    std::string filename_;
    std::shared_ptr<Data> blink_;
};


#endif //RYAN_TEACHING_WINTER_SESSION_SCORES_H
