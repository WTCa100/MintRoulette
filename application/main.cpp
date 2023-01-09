#include <iostream>
#include <ctime>

// Get header
#include "code/game/include/Menu.h"
#include "code/utilities/include/AppBuilder.h"

// Get source
#include "code/game/src/Menu.cpp"
#include "code/utilities/src/AppBuilder.cpp"

int main()
{
    AppBuilder* makeApp = new AppBuilder;
    makeApp->checkDirectories();
    delete makeApp;
    srand(static_cast<unsigned int>(time(NULL)));
    Menu* gameMenu = new Menu();
    gameMenu->mainMenuDisplay();
    delete gameMenu;
    return 0;
}