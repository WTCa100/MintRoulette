#include "../include/Menu.h"
#include <string>

void Menu::mainMenuDisplay()
{
    std::string choosenOption = "";
    do
    {
        std::cout << "Welcome to the mintRoulette!\t";
        std::cout << "Made by John \"WTCa100\" Bielawa\n";
        std::cout << "Test your lucky pawn!\n";
        std::cout << "Option list {placeholder}\n";
        std::cout << "Select and option and hit enter\n";
        std::getline(std::cin, choosenOption);
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