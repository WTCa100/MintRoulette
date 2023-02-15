#include <iostream>
#include <ctime>

// Get header
#include "code/game/include/Menu.h"
#include "code/utilities/include/DebugLogger.h"
#include "code/utilities/include/AppBuilder.h"

// Get source
#include "code/game/src/Menu.cpp"
#include "code/utilities/src/AppBuilder.cpp"

int main()
{


    DebugLogger* dbLog = new DebugLogger;
    dbLog->addDebugLog(
        {dbLog->dbLogAppOpen}
    );

    AppBuilder* makeApp = new AppBuilder(dbLog);
    makeApp->setupGameFiles();
    delete makeApp;
    
    // Generate seeds
    srand(static_cast<unsigned int>(time(NULL)));

    Menu* gameMenu = new Menu(dbLog);
    gameMenu->mainMenuDisplay();
    delete gameMenu;

    delete dbLog;

    return 0;
}