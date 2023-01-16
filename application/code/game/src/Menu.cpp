#include <string>
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
    // List all players bit withouth pathing
    for(auto& player : avilableFiles)
    {
        player.erase(player.begin(), player.begin() + player.rfind("\\") + 1);
        std::cout << "Debug: List: Players: File: Names: " << player << std::endl;
    }


    std::cout << "Player list!\n";
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
    std::vector<std::string> files;
    const std::string statsPath = FILE_PLAYER_STATS_PATH;
    for(const auto& entry : std::experimental::filesystem::directory_iterator(statsPath))
    {
        std::string strPath{entry.path().string()};
        files.push_back(strPath);
    }
    for(auto test : files)
    {
        std::cout << "Debug: Files: Path: Display: " << test << std::endl;
    }
    return files;
}