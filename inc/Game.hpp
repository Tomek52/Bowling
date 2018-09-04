#pragma once
#include <string>
#include <algorithm>

#include "Frame.hpp"

class Game
{
    std::string name_;
    Frame frame_[12];
public:
    explicit Game(const std::string & name = "");
    std::string getName() const;
    int score() const;
    int checkValue(const std::string & value);
    void setIsStrikeOrSpare(unsigned short int position, const std::string& value);
    Frame getFrame(unsigned short int position);
    
};