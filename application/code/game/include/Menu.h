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
    static void mainMenuDisplay();
    static void startNewGame();
    static void playerList();
    static void gameList();
    static void confirmExit();
};