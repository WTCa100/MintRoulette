#include <string>

// Get header
#include "../include/Menu.h"
#include "../../utilities/include/InputValidator.h"
#include "../include/Game.h"

// Get source
#include "../../utilities/src/InputValidator.cpp"
#include "../src/Game.cpp"

void Menu::mainMenuDisplay()
{
    std::string choosenOption = "";
    do
    {
        choosenOption.clear();
        std::cout << "Welcome to the mintRoulette!\t";
        std::cout << "Made by John \"WTCa100\" Bielawa\n";
        std::cout << "Test your lucky pawn!\n";
        std::cout << "Option list {placeholder}\n";
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
        case StartNewGame:
            startNewGame();
            break;
        case ShowPlayerList:
            playerList();
            break;
        case ShowGameList:
            gameList();
            break;
        case Exit:
            confirmExit();
            break;
        default:
            std::cout << "No such option!\n";
            break;
        }
    } while (std::stoi(choosenOption) != options::Exit);
    
}

void Menu::startNewGame()
{
    std::cout << "Start new game!\n";
    std::cout << "WIP!\n";
    Game* session = new Game();
    session->startGame();
    delete session;
}

void Menu::playerList()
{
    std::cout << "Player list!\n";
}

void Menu::gameList()
{
    std::cout << "Game list!\n";
}

void Menu::confirmExit()
{
    std::cout << "You sure you want to exit?\n";
}