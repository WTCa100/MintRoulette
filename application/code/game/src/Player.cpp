#include <iostream>

#include "../include/Player.h"
/// @brief displays if player lost or won money.
void Player::displayMoneyWonLoss(int initBankBalance)
{
    std::cout << "Player " << nickName_;
    if(moneyAccumulated_ == 0)
    {
        std::cout << " have won no money and ";
    }
    else if(moneyAccumulated_ > 0)
    {
        std::cout << " have won: " << moneyAccumulated_ 
        <<" and ";
    }
    if(moneyLost_ == 0)
    {
        std::cout << " have lost no money";
    }
    else
    {
        std::cout << "lost " << moneyLost_;
    }
    std::cout << "!" << std::endl;

    std::cout<< nickName_ << " ended the game with " << balance_ << " which is ";
    if(balance_ - initBankBalance > 0)
    {
        std::cout << balance_ - initBankBalance << " more than the starting ammount\n";
    }
    else if (balance_ - initBankBalance < 0)
    {
         std::cout <<initBankBalance - balance_ << " less than the starting ammount\n";
    }
    else
    {
        std::cout << " the same as the starting ammount\n";
    }
    

}

/// @brief Displays betCount_ and passCount_ logically correct
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

/**
 * @brief Changes the global bet value dividing globGoodBetCount by globBetCount
 * 
 * @param globGoodBetCount 
 * @param globBetCount 
 */
void Player::setGlobalGoodBetRatio(const uint32_t& globGoodBetCount, const uint32_t& globBetCount)
{
    if(globBetCount == 0)
    {
        std::cout << "Cannot devide by zero\n";
        return;
    }


    double newValue = static_cast<double>(globGoodBetCount) / static_cast<double>(globBetCount);
    std::cout << "GoodBet: " << globGoodBetCount << std::endl;
    std::cout << "BetCount: " << globBetCount << std::endl;
    setGlobalGoodBetRatio(newValue);
}

/// @brief Constructor used for saving and loading player data from and to file
/// @param nickName user name
/// @param globMoneyAccumulated how many player have accumulated during all of his playthroughs
/// @param globalMoneyLost how much money did player lost during all of his playthroughs
/// @param globGoodBetCount how many bets that player placed were good
/// @param globBetCount how many bets in general player have placed
/// @param globPassCount how many passes he has done
/// @param balance initial bank balance (at start of the game) / default is 0
/// @note balance is optional flag
Player::Player(const std::string nickName, int globMoneyAccumulated,
               int globMoneyLost, uint32_t globGoodBetCount, 
               uint32_t globBetCount, uint32_t globPassCount, 
               DebugLogger* dbLog, double globGoodBetRatio, int playerOrder, int balance)
{
    // Setup global variables
    nickName_ = nickName;
    globBetCount_ = globBetCount;
    globGoodBetCount_ = globGoodBetCount;
    globPassCount_ = globPassCount;
    globMoneyAccumulated_ = globMoneyAccumulated;
    globMoneyLost_ = globMoneyLost;
    globGoodBetRatio_ = globGoodBetRatio;

    // Setup local variables
    balance_ = balance;
    moneyLost_ = 0;
    moneyAccumulated_ = 0;
    passCount_ = 0;
    betCount_ = 0;
    goodBetCount_ = 0;
    playerOrderNumber_ = playerOrder;

    // Misc
    dbLog_ = dbLog;

    dbLog_->addDebugLog(
        {dbLog_->dbLogPlayerInitializedValues(nickName_, globMoneyAccumulated_,
                                              globMoneyLost_, globGoodBetCount_,
                                              globBetCount_, globPassCount_,
                                              balance, globGoodBetRatio_,
                                              playerOrderNumber_, false)}
    );

    dbLog_->buildDebugLogs();

}

/// @brief Constructor used as default when initial value of balance is set
/// @param balance inistial value of bank ammount 
Player::Player(int balance, int playerOrder, DebugLogger* dbLog, bool isPlayerBot)
{
    // Global
    nickName_ = "";
    globBetCount_ = 0;
    globGoodBetCount_ = 0;
    globMoneyAccumulated_ = 0;
    globMoneyLost_ = 0;    
    globPassCount_ = 0;
    globGoodBetRatio_ = 0;

    // Local
    balance_ = balance;
    moneyAccumulated_ = 0;
    moneyLost_ = 0;
    moneyLost_ = 0;
    betCount_ = 0;
    passCount_ = 0;
    goodBetCount_ = 0;
    playerOrderNumber_ = playerOrder;
    isPlayerBot_ = isPlayerBot;

    // Misc
    dbLog_ = dbLog;

    dbLog_->addDebugLog(
        {dbLog_->dbLogPlayerInitializedValues(nickName_, globMoneyAccumulated_,
                                              globMoneyLost_, globGoodBetCount_,
                                              globBetCount_, globPassCount_,
                                              balance, globGoodBetRatio_, 
                                              playerOrderNumber_, isPlayerBot_)}
    );

    dbLog_->buildDebugLogs();

}

/// @brief Constructor currently with no use
/// @param nickName player name
/// @param balance inital bank balance
Player::Player(const std::string nickName, int balance, DebugLogger* dbLog, bool isPlayerBot, int playerOrder)
{
    // Global
    nickName_ = nickName; 
    globBetCount_ = 0;
    globGoodBetCount_ = 0;
    globMoneyAccumulated_ = 0;
    globMoneyLost_ = 0;
    globPassCount_ = 0;
    globGoodBetRatio_ = 0;
    
    // Local
    balance_ = balance;
    moneyAccumulated_ = 0;
    moneyLost_ = 0;
    betCount_ = 0;
    passCount_ = 0;
    goodBetCount_ = 0;
    playerOrderNumber_ = playerOrder;
    isPlayerBot_ = isPlayerBot;
    
    // Misc
    dbLog_ = dbLog;

    dbLog_->addDebugLog(
        {dbLog_->dbLogPlayerInitializedValues(nickName_, globMoneyAccumulated_,
                                              globMoneyLost_, globGoodBetCount_,
                                              globBetCount_, globPassCount_,
                                              balance, globGoodBetRatio_, 
                                              playerOrderNumber_, isPlayerBot_)}
    );

    dbLog_->buildDebugLogs(); 

}

/// @brief Assings current local stats of player to it's global equivalents
void Player::moveToGlobalStats()
{

    dbLog_->addDebugLog(
        {dbLog_->dbLogGamePlayerMoveToGlobal(nickName_,
        {static_cast<int>(globPassCount_), static_cast<int>(globBetCount_), static_cast<int>(globGoodBetCount_), globMoneyAccumulated_, globMoneyLost_},
        {static_cast<int>(passCount_), static_cast<int>(betCount_), static_cast<int>(goodBetCount_), moneyAccumulated_, moneyLost_},
         globGoodBetRatio_)}
    );

    globPassCount_ += passCount_;
    globBetCount_ += betCount_;
    globGoodBetCount_ += goodBetCount_;
    globMoneyAccumulated_ += moneyAccumulated_;
    globMoneyLost_ += moneyLost_;
    if(globBetCount_ != 0)
    {
        setGlobalGoodBetRatio(globGoodBetCount_, globBetCount_);
    }
    else
    {
        globGoodBetRatio_ = 0;
    }

    dbLog_->buildDebugLogs();



}