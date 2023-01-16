#pragma once

#include <iostream>
#include <vector>

#include "../../utilities/include/FileManager.h"

// Link source files
enum options
{
    StartNewGame = 1,
    ShowPlayerList = 2,
    ShowGameList = 3,
    Exit = 4
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
    
    Menu() {fManager_ = new FileManager;};
    ~Menu() {delete fManager_;}

    private:
    FileManager* fManager_;

};