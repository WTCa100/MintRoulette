#include <ctime>
#include <limits.h>

#include "../include/Game.h"
#include "../../utilities/include/InputValidator.h"
#include "../../utilities/include/MaxValues.h"

void Game::setGameConfig()
{
    std::string userInput = "";
    bool isInputGood = false;
    // Ask for player count info
    {
        std::cout << "How many players will play (max 8)\n";
        do
        {
            std::getline(std::cin, userInput);
            if(ValidateInput::isStringNumber(userInput))
            {
                if(std::stoi(userInput) <= MAX_PLAYERS_PER_SESSION)
                {
                    isInputGood = true;
                }
                else
                {
                    std::cout << "Max player count is 8!\n";
                }
            }
            else
            {
                std::cout << "Input must be a numeric value!\n";
            }
        } while (!isInputGood);
        // Everything in order we can set config count
        setPlayerCount(std::stoi(userInput));
    }
    // Ask for player initial bank balance info
    {
        isInputGood = false;
        userInput.clear();
        std::cout << "What will be the initial bank balance?\n";
        do
        {
            std::getline(std::cin, userInput);
            if(ValidateInput::isStringNumber(userInput))
            {
                if(std::stoi(userInput) <= INT_MAX / 4)
                {
                    isInputGood = true;
                }   
                else
                {
                    std::cout << "Value cannot be greater than " << INT_MAX / 4 << std::endl; 
                }
            }
            else
            {
                std::cout << "Input must be a numeric value!\n";
            }
        } while (!isInputGood);
        setInitialBankBalance(std::stoi(userInput));
    }
}

void Game::startGame()
{
    std::cout << "WIP!\n";
    std::cout << "Player count: " << numberOfPlayers_ << std::endl;
    std::cout << "Init balance: " << initBankBalance_ << std::endl;
    std::cout << "Teardown\n";
}

Game::Game()
{
    setGameConfig();
}