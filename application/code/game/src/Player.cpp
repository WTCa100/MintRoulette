#include <iostream>

#include "../include/Player.h"

void Player::displayMoneyWonLoss()
{
    std::cout << "Player " << nickName_;
    if(moneyAccumulated_ < 0)
    {
        std::cout << " have lost: " << moneyAccumulated_ 
        << std::endl;
    }
    else if(moneyAccumulated_ > 0)
    {
        std::cout << " have won: " << moneyAccumulated_ 
        << std::endl;
    }
}

void Player::displayBetPassCounts()
{
    std::cout << "Player " << nickName_ << " placed ";
    if(betCount_ > 0)
    {
        std::cout << betCount_ << " bets ";
    }
    else
    {
        std::cout << "no bets ";
    }
    std::cout << "and ";
    if(passCount_ > 0)
    {
        std::cout << passCount_ << " passes!\n";
    }
    else
    {
        std::cout << "no passes!\n";
    }
}