#pragma once

#include <iostream>

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

    Menu() = default;
    
    protected:
    void startNewGame();
    void playerList();
    void gameList();
    void confirmExit();

};