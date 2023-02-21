#include <string>
#include <algorithm>
#include <experimental/filesystem>

// Get header
#include "../include/Menu.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include "../../utilities/include/InputValidator.h"
#include "../../utilities/include/Paths.h"

// Get source
#include "../../utilities/src/InputValidator.cpp"
#include "./Game.cpp"

/// @brief Shows main menu with asking which action user wants to take next
void Menu::mainMenuDisplay()
{
    dbLog_->addDebugLog(
        {dbLog_->dbLogMenuMainMenuDisplay}
    );
    dbLog_->buildDebugLogs();

    std::string choosenOption = "";
    do
    {
        choosenOption.clear();
        std::cout << "Welcome to the mintRoulette!\n";
        std::cout << "(Version: " << fManager_->extractConfigValueFromTag("gameVersion") << ") \n";
        std::cout << "Made by John \"WTCa100\" Bielawa\n";
        std::cout << "Test your lucky pawn!\n";
        std::cout << "1. New game\n";
        std::cout << "2. Players list\n";
        std::cout << "3. Game Lists\n";
        std::cout << "4. Exit\n";
        std::cout << "Select and option and hit enter\n";
        do
        {


            std::getline(std::cin, choosenOption);

            dbLog_->addDebugLog(
                {dbLog_->dbLogMenuGetInput,
                 dbLog_->dbLogMenuCheckUserInput(choosenOption, ValidateInput::isStringNumber(choosenOption))}
            );

            dbLog_->buildDebugLogs();

            if(!ValidateInput::isStringNumber(choosenOption))
            {
                std::cout << "You may only enter a numeric value!\n";         
            }
        } while (!ValidateInput::isStringNumber(choosenOption));
        
        switch (std::stoi(choosenOption))
        {
        case options::StartNewGame:

            dbLog_->addDebugLog(
                {dbLog_->dbLogMenuChoosenOption("StartNewGame")}
            );

            startNewGame();
            break;
        case options::ShowPlayerList:
            playerList();

            dbLog_->addDebugLog(
                {dbLog_->dbLogMenuChoosenOption("ShowPlayerList")}
            );            

            break;
        case options::ShowGameList:
            gameList();

            dbLog_->addDebugLog(
                {dbLog_->dbLogMenuChoosenOption("ShowGameList")}
            );

            break;
        case options::Exit:

            dbLog_->addDebugLog(
                {dbLog_->dbLogMenuChoosenOption("Exit")}
            );

            std::cout << "See you again next time!\n";

            break;
        default:
            std::cout << "No such option!\n";
            system("pause");
            system("cls");
            break;
        }

        dbLog_->buildDebugLogs();
        
    } while (std::stoi(choosenOption) != options::Exit);
    
}

/// @brief Create game instance
void Menu::startNewGame()
{

    system("cls");    
    std::cout << "Start new game!\n";
    Game* session = new Game(dbLog_, fManager_);
    session->startGame();
    delete session;

    system("pause");
    system("cls");

}

/// @brief Show lists of players and higscores
void Menu::playerList()
{

    system("cls");
    std::vector <Player*> savedPlayers = loadEveryPlayerStat();
    std::string optionChoosen;
    do
    {
        std::cout << "Player list!\n";
        std::cout << "Options are: \n";
        std::cout << "1. Show highscores\n";
        std::cout << "2. List all player names\n";
        std::cout << "3. Go back\n";
        do
        {
            std::getline(std::cin, optionChoosen);
            if(!ValidateInput::isStringNumber(optionChoosen))
            {
                std::cout << "Please select a valid option\n";
            }
        } while (!ValidateInput::isStringNumber(optionChoosen));
        PlayerListsOptions declearedOption = static_cast<PlayerListsOptions>(std::stoi(optionChoosen));
        switch (declearedOption)
        {
        case PlayerListsOptions::ShowHighscores:
            std::cout << "Showing Top-10 users!\n";
            showHighscores();
            break;
        case PlayerListsOptions::ShowFullList:
            std::cout << "Showing full list:\n";
            displayFullPlayerList(savedPlayers);
            break;
        case PlayerListsOptions::ExitListDisplay:
        default:
            break;
        }

    } while (static_cast<PlayerListsOptions>(std::stoi(optionChoosen)) != PlayerListsOptions::ExitListDisplay);
    // Teardown loaded content
    for(auto player : savedPlayers)
    {
        delete player;
    }
    system("cls");
}

void Menu::showHighscores()
{
    system("cls");

    // Load contents of highscores.csv
    std::vector<std::string> highscoresContent = fManager_->loadFileContent(FILE_PLAYER_HIGHSCORES_PATH, FILE_PLAYER_HIGHSCORES);
    std::vector<Player*> laterDisplay;

    // In order style the text we need to separate informations from the highscores
    std::cout << "Place:\tRatio:\tName:\n";
    for(auto rawLine : highscoresContent)
    {
        if(rawLine == "PlaceNo,BetRatio,Name")
        {
            continue;
        }
        std::string place, ratio, name;
        // Get place
        place = rawLine;
        place.erase(place.begin() + place.find(",") + 1, place.end());

        // Get ratio
        ratio = rawLine;
        ratio.erase(ratio.begin(), ratio.begin() + ratio.find(",") + 1);
        ratio.erase(ratio.begin() + ratio.rfind(",") + 1, ratio.end());

        // Get name
        name = rawLine;
        name.erase(name.begin(), name.begin() + + name.rfind(",") + 1);

        // Display properties 
        std::cout << place << "\t" << ratio << "\t" << name << std::endl;

        if(fManager_->isFileGood(FILE_PLAYER_STATS_PATH, name + EXT_PLAYER_STATS))
        {
            laterDisplay.push_back(fManager_->makePlayerFromLoadedFile(name));
        }
        else
        {
            std::cout << "System Message: Error! No such user found.\n";
        }

    }

    choosePlayerToDisplayDetails(loadEveryPlayerStat());
    system("cls");

    for(auto player : laterDisplay)
    {
        delete player;
    }

}

 std::vector<Player*> Menu::loadEveryPlayerStat()
 {
     // Load all avilable player files
    std::vector <std::string> avilableFiles = getPlayerStatsFiles();
    std::vector <Player*> savedPlayers;

    // List all players bit withouth pathing
    for(auto& player : avilableFiles)
    {
        player = fManager_->trimPath(player);
        savedPlayers.push_back(fManager_->makePlayerFromLoadedFile(player));
    }   

    return savedPlayers;
 }

/// @brief Show lists of games and it's log
void Menu::gameList()
{

    system("cls");

    dbLog_->addDebugLog(
        {dbLog_->dbLogMenuMainGameList}
    );

    dbLog_->buildDebugLogs();


    std::cout << "Game list!\n";
    std::vector<std::string> gamesFiles = fManager_->loadFilesFromPath(FILE_GAME_SAVE_LOG_PATH);

    dbLog_->addDebugLog(
        {dbLog_->dbLogMenuMainGameListDisplay(gamesFiles)}
    );

    dbLog_->buildDebugLogs();

    for(auto& gamePath : gamesFiles)
    {
        if(fManager_->isEntryFolder(gamePath))
        {
            continue;
        }

        gamePath = fManager_->trimPath(gamePath);
    }

    std::vector<std::string> gameIDs = gamesFiles;
    for(auto& Id : gameIDs)
    {
        Id.erase(Id.begin(), Id.begin() + 6);
    }

    chooseGameToDisplayLogs(gameIDs, gamesFiles);

}


std::vector <std::string> Menu::getPlayerStatsFiles()
{
    std::vector<std::string> files = fManager_->loadFilesFromPath(FILE_PLAYER_STATS_PATH);
    return files;
}

void Menu::showPlayerStats(const Player& showPlayer)
{

    dbLog_->addDebugLog(
        {dbLog_->dbLogMenuMainPlayerListAttemptToShowDetails(showPlayer.getNickName())}
    );



    std::cout << "Player name: " << showPlayer.getNickName() <<std::endl;
    std::cout <<"Managed to placed " << showPlayer.getGlobalGoodBetCount() << " bets right\n";
    std::cout <<"Placed " << showPlayer.getGlobalBetCount() << " bets\n";
    std::cout <<"Passed " << showPlayer.getGlobalPassCount() << " times!\n";
    std::cout <<"Accumulated " << showPlayer.getGlobalMoneyAccumulated() << " ammount of money!\n";
    std::cout <<"Lost " << showPlayer.getGlobalMoneyLost() << " ammount of money!\n";
    std::cout <<"Good / Bad bet ratio: " << showPlayer.getGlobalGoodBetRatio() << std::endl;
}

void Menu::displayFullPlayerList(const std::vector<Player*>& listToDisplay)
{
    system("cls");
    dbLog_->addDebugLog(
        {dbLog_->dbLogMenuMainPlayerList}
    );

    dbLog_->buildDebugLogs();

    choosePlayerToDisplayDetails(listToDisplay);
    
}

 void Menu::choosePlayerToDisplayDetails(const std::vector<Player*>& listToDisplay)
 {

    dbLog_->addDebugLog(
        {dbLog_->dbLogMenuMainPlayerListChooseDetails}
    );

    dbLog_->buildDebugLogs();

        std::cout << "If you want to see someones detailed stats please write down their name\n";
        std::cout << "Take note that it is case sensitive\n";
        std::string checkForDetails;
        do
        {

        std::cout << "Press \"q\" to go back\n";
        for(int entryNo = 0; entryNo < listToDisplay.size(); entryNo++)
        {
            std::cout << entryNo + 1 << ": " << listToDisplay[entryNo]->getNickName() << std::endl;
            if(entryNo % 50 == 0 && entryNo != 0)
            {
                std::cout << "End of the page!\n";
                std::cin.get();
            }
        }                        

            std::cout << "Provide Player name: \n";
            checkForDetails.clear();
            std::getline(std::cin, checkForDetails);

            dbLog_->addDebugLog(
                {dbLog_->dbLogMenuGetInput,
                 dbLog_->dbLogMenuCheckUserInput(checkForDetails ,ValidateInput::stringToLower(checkForDetails) != "q" && ValidateInput::isADuplicatePlayer(listToDisplay, checkForDetails))}
            );

            if(ValidateInput::stringToLower(checkForDetails) != "q")
            {
                dbLog_->addDebugLog(
                    {dbLog_->dbLogMenuMainPlayerListAttemptToShowDetails(checkForDetails)}
                );

                // Search and display player
                if(ValidateInput::isADuplicatePlayer(listToDisplay, checkForDetails))
                {
                    for(auto player : listToDisplay)
                    {
                        if(player->getNickName() == checkForDetails)
                        {
                            showPlayerStats(*player);
                            system("Pause");
                            system("cls");
                            break;
                        }
                    }
                }
                else
                {
                    std::cout << "No such player found!\n";
                    system("Pause");
                    system("cls");

                }           
                dbLog_->buildDebugLogs();
            }
        } while (ValidateInput::stringToLower(checkForDetails) != "q");
        system("cls");
 }

void Menu::showGameSave(const uint16_t& gameId)
{
    std::ifstream gameSaveFile;
    std::string gameSavePath = FILE_GAME_SAVE_LOG_PATH;
    gameSaveFile.open(gameSavePath + "/GameNr" + std::to_string(gameId) + EXT_GAME_LOG);
    if(!gameSaveFile.is_open())
    {
        std::cout << "No Game with number " + std::to_string(gameId) + " found!\n";
        return;
    }

    std::string showLine;
    while(std::getline(gameSaveFile, showLine))
    {
        ///@todo Improve displaying functions (add for example pages)
        std::cout << showLine << std::endl;
    }

    system("Pause");
    system("cls");
}

void Menu::chooseGameToDisplayLogs(const std::vector<std::string>& fullGameIds, const std::vector<std::string>& fullGameList)
{
    std::cout << "If you want to see detailed logs please enter a game id\n";
    std::cout << "Take note that it is case sensitive\n";
    std::string checkForDetails;

    dbLog_->addDebugLog(
        {dbLog_->dbLogMenuGetInput}
    );

    do
    {
        std::cout << "Press \"q\" to go back\n";
        for(auto path : fullGameList)
        {
            std::cout << path << std::endl;
        }

        std::cout << "Provide game id: \n";
        checkForDetails.clear();
        std::getline(std::cin, checkForDetails);
        if(ValidateInput::stringToLower(checkForDetails) != "q")
        {

            dbLog_->addDebugLog(
                {dbLog_->dbLogGameGetInputCheck(checkForDetails, ValidateInput::isStringNumber(checkForDetails))}
            );

            if(ValidateInput::isStringNumber(checkForDetails))
            {
                showGameSave(static_cast<uint16_t>(std::stoi(checkForDetails)));
            }
            else
            {
                std::cout << "Please provide a numeric value!\n";
                system("Pause");                
            }

            dbLog_->buildDebugLogs();

        }


        system("cls");
    } while (ValidateInput::stringToLower(checkForDetails) != "q");
}

Menu::Menu(DebugLogger* dbLog)
{
    dbLog_ = dbLog;
    dbLog_->addDebugLog(
        {dbLog_->dbLogClassMenuInitialize}
    );

    fManager_ = new FileManager(dbLog_);
    dbLog_->buildDebugLogs();

}