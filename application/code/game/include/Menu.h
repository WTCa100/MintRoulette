#pragma once

#include <iostream>
#include <vector>

#include "../../utilities/include/FileManager.h"

enum options
{
    StartNewGame = 1,
    ShowPlayerList = 2,
    ShowGameList = 3,
    Exit = 4
};

enum PlayerListsOptions
{
    ShowHighscores = 1,
    ShowFullList = 2,
    ExitListDisplay = 3
};

class Menu
{
    public:
    void mainMenuDisplay();
    void startNewGame();
    void playerList();
    void gameList();
    void confirmExit();
    std::vector <std::string> getPlayerStatsFiles();
    void showPlayerStats(const Player& showPlayer);
    void showGameSave(const uint16_t& gameId);
    void showHighscores();
    std::vector<Player*> loadEveryPlayerStat();
    void displayFullPlayerList(const std::vector<Player*>& listToDisplay);
    void chooseGameToDisplayLogs(const std::vector<std::string>& fullGameList);
    void choosePlayerToDisplayDetails(const std::vector<Player*>& listToDisplay);
    
    Menu() {fManager_ = new FileManager;};
    ~Menu() {delete fManager_;}

    private:
    FileManager* fManager_;

};