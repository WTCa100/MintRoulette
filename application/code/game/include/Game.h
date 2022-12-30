#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Game
{
    public:
    void gameConfig();
    void startNewGame();

    private:
    std::map<std::string, uint16_t> playerSet_;
    std::vector<std::string> playerNames_;
};