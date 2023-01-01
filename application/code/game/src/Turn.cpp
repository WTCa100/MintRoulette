#include <iostream>
#include <ctime>

#include "../include/Turn.h"

uint16_t Turn::rollTheRoulette()
{
    srand(static_cast<unsigned int>(time(NULL)));
    return static_cast<uint16_t>(rand()% 37);
}

void Turn::bettingPhase()
{
    for(int i = 0; i < currentPlayers_.size(); i++)
    {
        std::cout << "Debug info: " << currentPlayers_[i]->getNickName() << " turn has started\n";
        std::cout << "It's " << currentPlayers_[i]->getNickName() << "'s turn\n";
        std::cout << "You have: " << currentPlayers_[i]->getBalance() << " worth of balance\n";
        std::cout << "Are you betting or passing?\n";
        std::cout << "Debug info: " << currentPlayers_[i]->getNickName() << " turn has ended\n";
    }
}

void Turn::playTurn()
{
    std::cout << "Turn " << turnNumber_ << std::endl;
    bettingPhase();
    setLuckyNumber(rollTheRoulette());
}

Turn::~Turn()
{
    std::cout << "End of turn: " << turnNumber_ << "!\n";
}