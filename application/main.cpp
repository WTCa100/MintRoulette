#include <iostream>

// Get header
#include "code/game/include/Menu.h"

// Get source
#include "code/game/src/Menu.cpp"

int main()
{
    Menu* gameMenu = new Menu();
    gameMenu->mainMenuDisplay();
    delete gameMenu;
    return 0;
}