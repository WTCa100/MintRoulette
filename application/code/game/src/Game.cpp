#include <ctime>
#include <limits.h>
#include <algorithm>

// Get header
#include "../include/Game.h"
#include "../include/Turn.h"
#include "../../utilities/include/InputValidator.h"
#include "../../utilities/include/MaxValues.h"

// Get source
#include "./Turn.cpp"
#include "../src/Player.cpp"

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
            do
            {
                std::getline(std::cin, tmpNicknameHolder);
                if(tmpNicknameHolder.empty())
                {
                    std::cout << "Player must have a name!\n";
                }
            } while (tmpNicknameHolder.empty());
            if(ValidateInput::isADuplicatePlayer(players_, tmpNicknameHolder))
            {
                std::cout << "2 Players cannot have the same nickname!\n";
            }
        } while (ValidateInput::isADuplicatePlayer(players_, tmpNicknameHolder));
        
        roulettePlayer->setNickName(tmpNicknameHolder);
        players_.push_back(roulettePlayer);
    }
    playersAlive_ = players_;
    std::cout <<"there are " << playersAlive_.size() << " players\n";
    for(auto i : players_)
    {
        std::cout << "Player nick: " << i->getNickName() << std::endl;
    }
    // Start turns
    std::cout << "Debug info: Start of turns\n";
    bool canGameProgress = true;
    uint16_t turnId = 0;
    while(canGameProgress)
    {
        turnId ++;
        bool stopGameEarly = false;
        Turn* currentTurn = new Turn(playersAlive_, turnId);
        currentTurn->playTurn();
        gameTurns_.push_back(currentTurn);
        playersAndBetsSave_.push_back(currentTurn->getPlayersBets());
        eliminatePlayers();
        // Here check if game can progress (for example if there is at least 2 players with more than 1 in their bank)
        // If not, end and ask if player wants to save the game
        // If yes, ask if players would like to continue the game or end
        // If they would like to end ask for save again
        stopGameEarly = askForStopGameEarly(stopGameEarly);
        canGameProgress = checkGameCondition(stopGameEarly);
    }
}

void Game::eliminatePlayers()
{
    for(auto& checkPlayer : playersAlive_)
    {
        if(checkPlayer->getBalance() == 0)
        {
            std::cout << "Player: " << checkPlayer->getNickName() << " got eliminated!\n";
            playersEliminated_.push_back(checkPlayer);
        }
    }
    for(auto& killPlayer : playersEliminated_)
    {
        playersAlive_.erase(std::remove(playersAlive_.begin(), playersAlive_.end(), killPlayer), playersAlive_.end());
    }
}

bool Game::isStringValid(const std::string& userInput)
{
    return (tolower(userInput[0]) == 'y' ||
            tolower(userInput[0]) == 'n');
}

bool Game::askForStopGameEarly(bool& stopEarly)
{
    std::string userInput = "";
    std::cout << "Do you wish to proccede? y/n\n";
    do
    {
        std::getline(std::cin, userInput);
        if(!this->isStringValid(userInput))
        {
            std::cout << "It's either yes or no\n";
        }
    } while (!this->isStringValid(userInput));

    if(tolower(userInput[0]) == 'y')
    {
        return false;
    }
    return true;
}

/// @brief Checks if game is eligable for further progression
/// @param canGameProgress
/// @todo Ask if player wants to continue games
/// @return 1: can progress 0: cannot progress
bool Game::checkGameCondition(const bool& stopEarly)
{
    if(playersAlive_.size() <= 1)
    {
        return false;
    }
    if(stopEarly)
    {
        return false;
    }
    return true;
}

/// @brief Summerizes game progres
void Game::endScreen()
{
    std::cout << "Game summary\n";
    for(auto& players : players_)
    {
        players->displayMoneyWonLoss();
        players->displayBetPassCounts();
    }
}

Game::Game()
{
    setGameConfig();
}

Game::~Game()
{
    endScreen();
    std::cout << "Teardown game\n";
    std::cout << "Debug: Info: Players: Alive: Clear\n";
    playersAlive_.clear(); 
    std::cout << "Debug: Info: Players: Elimineted: Clear\n";
    playersEliminated_.clear(); 
    for(auto i = 0; i < playersAndBetsSave_.size(); i++)
    {
        std::cout << "Turn: " << i << std::endl;
        for(auto& j : playersAndBetsSave_[i])
        {
            std::cout << "Debug: Deleting bet for " << j.first->getNickName() << std::endl;
            std::cout << "Debug: Bet info: Type:" << j.second->getBetType() << std::endl;
            std::cout << "Debug: Bet info: Value: " << j.second->getAmmountBetted() << std::endl;
        }
    }
    
    for(auto i = 0; i < gameTurns_.size(); i++)
    {
        std::cout << "Debug Info: Delete turn " << i << std::endl;
        delete gameTurns_[i];
    }
    for(auto i = 0; i < players_.size(); i++)
    {
        std::cout << "Debug Info: Delete player " << i + 1 << std::endl;
        delete players_[i];
    }
}