#include <iostream>
#include <windows.h>

// Get header
#include "../include/Turn.h"
#include "../include/Bet.h"

// Get source
#include "./Bet.cpp"

uint16_t Turn::randomizeNumber()
{
    return static_cast<uint16_t>(rand()% 37);
}

void Turn::bettingPhase()
{
    for(int i = 0; i < currentPlayers_.size(); i++)
    {
        std::cout << "Debug info: " << currentPlayers_[i]->getNickName() << " turn has started\n";
        std::cout << "It's " << currentPlayers_[i]->getNickName() << "'s turn\n";
        std::cout << "You have: " << currentPlayers_[i]->getBalance() << " worth of balance\n";
        // Aske player if he wants to bet
        if(askForBet())
        {
            Bet* playerBet = new Bet();
            playerBet->askForBetType(*currentPlayers_[i]);
            delete playerBet;
        }        
        else
        {
            Bet* playerPass = new Bet(*currentPlayers_[i]);
            delete playerPass;
        }
        
        std::cout << "Debug info: " << currentPlayers_[i]->getNickName() << " turn has ended\n";
    }
}

void Turn::rollTheRoulette()
{

    std::vector<uint16_t> numbers(3, 0);
    for(auto &i : numbers)
    {
        i = randomizeNumber();
    }
    std::cout << numbers.size() << std::endl;
    size_t luckyNumPos = rand() % numbers.size();
    setLuckyNumber(numbers[luckyNumPos]);
    std::cout << "Bets are now clossed!\n";
    std::cout << "The roulette is being rolled\n";
    for(int i = 0; i < numbers.size(); i++)
    {
        std::cout << numbers[i] << "    ";
        Sleep(1000); 
    }
    std::cout << std::endl;
    std::cout << "The lucky number is: ";
    Sleep(1000);
    std::cout << luckyNumber_ << std::endl;
}

bool Turn::askForBet()
{
    std::string userInput;
    std::cout << "Are you betting or passing?\n";
    do
    {
        "1. Yes\n";
        "2. No\n";
        do
        {
            std::getline(std::cin, userInput);
            if(!ValidateInput::isStringNumber(userInput))
            {
                std::cout << "You may enter only numeric value\n";
            }
        } while (!ValidateInput::isStringNumber(userInput));
        if(std::stoi(userInput) == 1)
        {
            return true;
        }
        else if(std::stoi(userInput) == 2)
        {
            return false;
        }
        else
        {
            std::cout << "It's either yes or no\n";
        }
    } while (!(std::stoi(userInput) == 1 || std::stoi(userInput) == 2));
    return false;
}

void Turn::playTurn()
{
    std::cout << "Turn " << turnNumber_ << std::endl;
    bettingPhase();
    rollTheRoulette();
}

Turn::~Turn()
{
    std::cout << "End of turn: " << turnNumber_ << "!\n";
}