#include "Game.hpp"
#include <algorithm>
#include <tuple>

Game::Game(const std::string & name) : name_(name)
{}

std::string Game::getName() const
{
    return name_;
}

int Game::score() const
{
    //needs implementation after made checkValueFrame()
    return 0;
}

void Game::setIsStrikeOrSpare(unsigned short int position, const std::string& value)
{
    if (value[0] == 'X')
    {
        frame_[position].setIsStrike();
    }
    if (value.size() == 2 and value[1] == '/')
    {
        frame_[position].setIsSpare();
    }
}

std::pair <int, int> Game::checkValue(const std::string& value)
{
    int firstBall = 0;
    int secondBall = 0;

    auto valueTemp = value.substr(0, 2);
    std::replace(valueTemp.begin(), valueTemp.end(), '-', '0');

    if (value[0] == 'X') firstBall = 10;
    else if (value[1] == '/') 
    {
        firstBall = std::stoi(valueTemp.substr(0, 1));
        secondBall = 10 - firstBall;
    }
    else
    {
        firstBall = std::stoi(valueTemp.substr(0, 1));
        secondBall = std::stoi(valueTemp.substr(1, 1));
    }

    return std::make_pair(firstBall, secondBall);
}

Frame Game::getFrame(unsigned short int position)
{
    return frame_[position];
}

void Game::setValueFrameAndPrevFrames(int pos, const std::string& value)
{
    int firstBall, secondBall;
    std::tie(firstBall, secondBall) = checkValue(value);

    frame_[pos].setValue(firstBall + secondBall);
    setIsStrikeOrSpare(pos, value);
    
    if(pos > 1 and frame_[pos - 2].isStrike())
    {
        if(frame_[pos - 1].isStrike())
        {
            frame_[pos - 2].addValue(10 + firstBall);
        }
        else
        {
            frame_[pos - 2].addValue(frame_[pos - 1].getValue());
        }
    }
    if(pos > 0 and frame_[pos - 1].isSpare())
    {
        frame_[pos - 1].addValue(firstBall);
    }
}
