#include <ctime>
#include <limits.h>

// Get header
#include "../include/Game.h"
#include "../include/Turn.h"
#include "../../utilities/include/InputValidator.h"
#include "../../utilities/include/MaxValues.h"

// Get source
#include "./Turn.cpp"

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
                if(std::stoi(userInput) <= MAX_PLAYERS_PER_SESSION && std::stoi(userInput) > 1)
                {
                    isInputGood = true;
                }
                else
                {
                    std::cout << "Max player count is 8, and there must be at least one player\n";
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
                if(std::stoi(userInput) <= INT_MAX / 4 && std::stoi(userInput) >= 100)
                {
                    isInputGood = true;
                }   
                else
                {
                    std::cout << "Value cannot be greater than " << INT_MAX / 4 
                              << " and cannot be lower than 100!" << std::endl; 
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

    for(int i = 0; i < numberOfPlayers_; i++)
    {
        std::string tmpNicknameHolder = "";
        Player* roulettePlayer = new Player(initBankBalance_);
        std::cout << "Please provide name for player " << i + 1 << std::endl;
        do
        {
            std::getline(std::cin, tmpNicknameHolder);
            if(tmpNicknameHolder.empty())
            {
                std::cout << "Player must have a name!\n";
            }
        } while (tmpNicknameHolder.empty());
        roulettePlayer->setNickName(tmpNicknameHolder);
        players_.push_back(roulettePlayer);
    }
    std::cout <<"there are " << players_.size() << " players\n";
    for(auto i : players_)
    {
        std::cout << "Player nick: " << i->getNickName() << std::endl;
    }
    // Start turns
    std::cout << "Debug info: Start of turns\n";
    for(int i = 0; i < 5; i++)
    {
        Turn* currentTurn = new Turn(players_, i);
        currentTurn->playTurn();
        delete currentTurn;
    }
}

Game::Game()
{
    setGameConfig();
}

Game::~Game()
{
    std::cout << "Teardown game\n";
    for(auto i = 0; i < gameTurns_.size(); i++)
    {
        std::cout << "Debug Info: Delete turn " << i << std::endl;
        //delete gameTurns_[i];
    }
    for(auto i = 0; i < players_.size(); i++)
    {
        std::cout << "Debug Info: Delete player " << i + 1 << std::endl;
        delete players_[i];
    }
}