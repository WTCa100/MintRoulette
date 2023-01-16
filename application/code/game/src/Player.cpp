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

/// @brief Constructor used for saving and loading
/// @param nickName user name
/// @param globMoneyAccumulated how many player have accumulated during all of his playthroughs
/// @param globGoodBetCount how many bets that player placed were good
/// @param globBetCount how many bets in general player have placed
/// @param globPassCount how many passes he has done
/// @param balance initial bank balance (at start of the game) / default is 0
/// @note balance is optional flag
Player::Player(const std::string nickName, int globMoneyAccumulated, uint32_t globGoodBetCount, uint32_t globBetCount,
               uint32_t globPassCount, int balance)
{
    // Setup global variables
    nickName_ = nickName;
    globBetCount_ = globBetCount;
    globGoodBetCount_ = globGoodBetCount;
    globPassCount_ = globPassCount;

    // Setup local variables
    balance_ = balance;
    moneyAccumulated_ = 0;
    passCount_ = 0;
    betCount_ = 0;
    goodBetCount_ = 0;

}

/// @brief Constructor used as default when initial value of balance is set
/// @param balance inistial value of bank ammount 
Player::Player(int balance)
{
    // Global
    nickName_ = "";
    globBetCount_ = 0;
    globGoodBetCount_ = 0;
    globMoneyAccumulated_ = 0;
    globPassCount_ = 0;

    // Local
    balance_ = balance;
    moneyAccumulated_ = 0;
    betCount_ = 0;
    passCount_ = 0;
    goodBetCount_ = 0;
}

Player::Player(const std::string nickName, int balance)
{
    // Global
    nickName_ = nickName; 
    globBetCount_ = 0;
    globGoodBetCount_ = 0;
    globMoneyAccumulated_ = 0;
    globPassCount_ = 0;
    
    // Local
    balance_ = balance;
    moneyAccumulated_ = 0;
    betCount_ = 0;
    passCount_ = 0;
    goodBetCount_ = 0;
}

void Player::moveToGlobalStats()
{
    globPassCount_ += passCount_;
    globBetCount_ += betCount_;
    globGoodBetCount_ += goodBetCount_;
    globMoneyAccumulated_ += moneyAccumulated_;
}