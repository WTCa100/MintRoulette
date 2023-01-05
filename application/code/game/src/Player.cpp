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