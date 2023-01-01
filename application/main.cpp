#include <iostream>
#include <ctime>

// Get header
#include "code/game/include/Menu.h"

// Get source
#include "code/game/src/Menu.cpp"

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    Menu* gameMenu = new Menu();
    gameMenu->mainMenuDisplay();
    delete gameMenu;
    return 0;
}