#pragma once

#include <iostream>

// Link source files
enum options
{
    StartNewGame,
    ShowPlayerList,
    ShowGameList,
    Exit
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