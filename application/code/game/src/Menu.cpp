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
        std::cout << "Welcome to the mintRoulette!\t";
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

            confirmExit();
            break;
        default:
            std::cout << "No such option!\n";
            break;
        }

        dbLog_->buildDebugLogs();
        
    } while (std::stoi(choosenOption) != options::Exit);
    
}

/// @brief Create game instance
void Menu::startNewGame()
{

    std::cout << "Start new game!\n";
    std::cout << "WIP!\n";
    Game* session = new Game(dbLog_, fManager_);
    session->startGame();
    delete session;
}

/// @brief Show lists of players and higscores
void Menu::playerList()
{

    std::vector <Player*> savedPlayers = loadEveryPlayerStat();
    std::string optionChoosen;

    
    do
    {
        std::cout << "Player list!\n";
        std::cout << "Options are: \n";
        std::cout << "1. Show highscores WIP\n";
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
}

void Menu::showHighscores()
{
    // Load contents of highscores.csv
    std::vector<std::string> highscoresContent = fManager_->loadFileContent(FILE_PLAYER_HIGHSCORES_PATH, FILE_PLAYER_HIGHSCORES);
    
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
    }

    choosePlayerToDisplayDetails(loadEveryPlayerStat());
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
        std::cout << "Debug: List: Players: File: Name: " << player << std::endl;
        savedPlayers.push_back(fManager_->makePlayerFromLoadedFile(player));
    }   

    return savedPlayers;
 }

/// @brief Show lists of games and it's log
void Menu::gameList()
{
    std::cout << "Game list!\n";
    std::vector<std::string> gamesFiles = fManager_->loadFilesFromPath(FILE_GAME_SAVE_LOG_PATH);
    for(auto gamePath : gamesFiles)
    {
        if(fManager_->isEntryFolder(gamePath))
        {
            continue;
        }

        gamePath = fManager_->trimPath(gamePath);
        std::cout << gamePath << std::endl;
    }

    std::vector<std::string> gameIDs = gamesFiles;
    for(auto& Id : gameIDs)
    {
        Id.erase(Id.begin(), Id.begin() + 6);
        std::cout << Id << std::endl;
    }

    chooseGameToDisplayLogs(gameIDs);

}

/// @brief Prompt user to double check 
void Menu::confirmExit()
{
    std::cout << "You sure you want to exit?\n";
}

std::vector <std::string> Menu::getPlayerStatsFiles()
{
    std::vector<std::string> files = fManager_->loadFilesFromPath(FILE_PLAYER_STATS_PATH);
    for(auto test : files)
    {
        std::cout << "Debug: Files: Path: Display: " << test << std::endl;
    }
    return files;
}

void Menu::showPlayerStats(const Player& showPlayer)
{
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
    for(int entryNo = 0; entryNo < listToDisplay.size(); entryNo++)
    {
        std::cout << entryNo + 1 << ": " << listToDisplay[entryNo]->getNickName() << std::endl;
        if(entryNo % 50 == 0 && entryNo != 0)
        {
            std::cout << "End of the page!\n";
            std::cin.get();
        }
    }
    choosePlayerToDisplayDetails(listToDisplay);

}

 void Menu::choosePlayerToDisplayDetails(const std::vector<Player*>& listToDisplay)
 {
        std::cout << "If you want to see someones detailed stats please write down their name\n";
        std::cout << "Take note that it is case sensitive\n";
        std::string checkForDetails;
        do
        {
            std::cout << "Provide Player name: \n";
            checkForDetails.clear();
            std::getline(std::cin, checkForDetails);
            if(ValidateInput::stringToLower(checkForDetails) != "q")
            {
                // Search and display player
                if(ValidateInput::isADuplicatePlayer(listToDisplay, checkForDetails))
                {
                    for(auto player : listToDisplay)
                    {
                        if(player->getNickName() == checkForDetails)
                        {
                            showPlayerStats(*player);
                            break;
                        }
                    }
                }
                else
                {
                    std::cout << "No such player found!\n";
                }
                std::cout << "Press any key to continue...\n";
                std::cin.get();                    
            }
        } while (ValidateInput::stringToLower(checkForDetails) != "q");
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
}

void Menu::chooseGameToDisplayLogs(const std::vector<std::string>& fullGameList)
{
    std::cout << "If you want to see detailed logs please enter a game id\n";
    std::cout << "Take note that it is case sensitive\n";
    std::cout << "If you want to exit from this section simply type 'q'\n";
    std::string checkForDetails;
    do
    {
        std::cout << "Provide game id: \n";
        checkForDetails.clear();
        std::getline(std::cin, checkForDetails);
        if(ValidateInput::stringToLower(checkForDetails) != "q")
        {
            if(ValidateInput::isStringNumber(checkForDetails))
            {
                showGameSave(static_cast<uint16_t>(std::stoi(checkForDetails)));
            }
            else
            {
                std::cout << "Please provide a numeric value!\n";
            }    
        }
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