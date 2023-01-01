#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "./Player.h"
#include "./Turn.h"

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
    ~Game();

    private:
    std::vector<Player*> players_;
    std::vector<Turn*> gameTurns_;
    uint16_t numberOfPlayers_;
    int initBankBalance_;
};