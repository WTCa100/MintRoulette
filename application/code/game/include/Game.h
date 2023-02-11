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
#include "../../utilities/include/Logger.h"

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
    uint16_t loadNextGameId();
    void updateHighscores();

    // Setters
    // Config
    void setPlayerCount(const uint16_t& numberOfPlayers) {numberOfPlayers_ = numberOfPlayers;}
    void setGameId(const uint16_t& gameId) {gameId_ = gameId;}
    // Default value is 1000 but player can change it
    void setInitialBankBalance(const int& initialBankBalance = 1000) {initBankBalance_ = initialBankBalance;}

    // Getters
    uint16_t getPlayerCount() {return numberOfPlayers_;}
    uint16_t getGameId() {return gameId_;}

    // Saving
    void savePlayerStats(const Player& savePlayer);

    Game(const FileManager* fManager);
    ~Game();

    private:
    std::vector<std::pair<double, std::string>> highscores_;
    bool inProgress_;
    bool hasBots_;
    uint16_t gameId_;
    FileManager* fManager_;
    Logger* gameLog_;
    std::vector <std::unordered_map<Player*, Bet*>> playersAndBetsSave_;
    std::vector<Player*> playersAlive_;
    std::vector<Player*> playersEliminated_;
    std::vector<Player*> players_;
    std::vector<Turn*> gameTurns_;
    uint16_t numberOfPlayers_;
    int initBankBalance_;
    uint16_t numOfBots_;
};