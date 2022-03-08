//
// Created by yiwei yang on 2/12/22.
//

#ifndef RYAN_TEACHING_WINTER_SESSION_SCORES_H
#define RYAN_TEACHING_WINTER_SESSION_SCORES_H

#include "EatKanoPanel.h"
#include <boost/shared_ptr.hpp>
#include <compare>
#include <list>
#include <string>

struct Data {
    Data();
    int score;
    double time;
    std::string name;
    std::weak_ordering operator<=>(const Data &rhs) const = default;
};

class Highscore {
public:
    explicit Highscore(EatKanoPanel::Mode type);
    [[nodiscard]] bool isHighscore(const Data &data) const;
    void draw() const;
    void Add(const Data &);
    void save() const;
    void Blink(Data);

private:
    std::list<Data> highscores_;
    EatKanoPanel::Mode type_;
    std::string filename_;
    std::shared_ptr<Data> blink_;
};

#endif // RYAN_TEACHING_WINTER_SESSION_SCORES_H
