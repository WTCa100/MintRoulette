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
            if(!ValidateInput::isStringNumber(choosenOption))
            {
                std::cout << "You may only enter a numeric value!\n";
            }
        } while (!ValidateInput::isStringNumber(choosenOption));
        
        switch (std::stoi(choosenOption))
        {
        case options::StartNewGame:
            startNewGame();
            break;
        case options::ShowPlayerList:
            playerList();
            break;
        case options::ShowGameList:
            gameList();
            break;
        case options::Exit:
            confirmExit();
            break;
        default:
            std::cout << "No such option!\n";
            break;
        }
    } while (std::stoi(choosenOption) != options::Exit);
    
}

/// @brief Create game instance
void Menu::startNewGame()
{

    std::cout << "Start new game!\n";
    std::cout << "WIP!\n";
    Game* session = new Game(fManager_);
    session->startGame();
    delete session;
}

/// @brief Show lists of players and higscores
void Menu::playerList()
{
    // Load information about every entry
    std::vector <std::string> avilableFiles = getPlayerStatsFiles();
    std::vector <Player*> savedPlayers;
    // Used for latter input
    std::string optionChoosen;
    // List all players bit withouth pathing
    for(auto& player : avilableFiles)
    {
        fManager_->trimPath(player);
        std::cout << "Debug: List: Players: File: Name: " << player << std::endl;
        savedPlayers.push_back(fManager_->makePlayerFromLoadedFile(player));
    }
    
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
            std::cout << "No highscores currently WIP!\n";
            break;
        case PlayerListsOptions::ShowFullList:
            std::cout << "Showing full list:\n";
            displayFullList(savedPlayers);
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

/// @brief Show lists of games and it's log
void Menu::gameList()
{
    std::cout << "Game list!\n";
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
    std::cout <<"And accumulated " << showPlayer.getGlobalMoneyAccumulated() << " ammount of money!\n";
}

void Menu::displayFullList(const std::vector<Player*>& listToDisplay)
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
