#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// Get header
#include "./Player.h"
#include "./Turn.h"
#include "./Bet.h"
#include "../../utilities/include/InputValidator.h"
#include "../../utilities/include/FileManager.h"

class Game : public ValidateInput
{
    public:
    void setGameConfig();
    void startGame();
    void eliminatePlayers();
    void endScreen();
    bool checkGameCondition(const bool& stopEarly);
    bool askForStopGameEarly(bool& stopEarly);
    bool isStringValid(const std::string& userInput) override;
    bool checkIfPlayerExists(const std::string& name) const;

    // Setters
    // Config
    void setPlayerCount(const uint16_t& numberOfPlayers) {numberOfPlayers_ = numberOfPlayers;}
    // Default value is 1000 but player can change it
    void setInitialBankBalance(const int& initialBankBalance = 1000) {initBankBalance_ = initialBankBalance;}

    // Saving
    void savePlayerStats(const Player& savePlayer);

    Game();
    ~Game();

    private:
    FileManager* fManager;
    std::vector <std::unordered_map<Player*, Bet*>> playersAndBetsSave_;
    std::vector<Player*> playersAlive_;
    std::vector<Player*> playersEliminated_;
    std::vector<Player*> players_;
    std::vector<Turn*> gameTurns_;
    uint16_t numberOfPlayers_;
    int initBankBalance_;
};