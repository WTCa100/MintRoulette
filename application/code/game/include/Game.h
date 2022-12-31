#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Game
{
    public:
    void setGameConfig();
    void startGame();
    // Setters
    // Config
    void setPlayerCount(const uint16_t& numberOfPlayers) {numberOfPlayers_ = numberOfPlayers;}
    // Default value is 1000 but player can change it
    void setInitialBankBalance(const int& initialBankBalance = 1000) {initBankBalance_ = initialBankBalance;}

    Game();

    private:
    // Map consists of player nickname and his bank balance.
    std::map<std::string, uint16_t> playerSet_;
    std::vector<std::string> playerNames_;
    uint16_t numberOfPlayers_;
    int initBankBalance_;
};