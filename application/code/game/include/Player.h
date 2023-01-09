#pragma once

#include <string>

class Player
{
    public:
    void displayMoneyWonLoss();
    void displayBetPassCounts();

    // Setters
    void setNickName(const std::string& nickName) { nickName_ = nickName;}
    void setBalance(const int& balance) { balance_ = balance;}
    void setMoneyAccumulated(const int& moneyAccumulated) {moneyAccumulated_ = moneyAccumulated;}
    void setBetAmmount(const uint32_t& betAmmount) {betAmmount_ = betAmmount;}
    void setBetCount(const uint32_t& betCount) {betCount_ = betCount;}
    void setPassCount(const uint32_t& passCount) {passCount_ = passCount;}

    // Getters
    std::string getNickName() const {return nickName_;}
    int getBalance() const {return balance_;}
    int getMoneyAccumulated() const {return moneyAccumulated_;}
    uint32_t getBetCount() const {return betCount_;}
    uint32_t getPassCount() const {return passCount_;}

    Player() = default;
    /// @brief Constructor used as default when initial value of balance is set
    /// @param balance inistial value of bank ammount 
    Player(int balance) {balance_ = balance; moneyAccumulated_ = 0; betCount_ = 0; passCount_ = 0;}
    Player(std::string nickName, int balance) {nickName_ = nickName; balance_ = balance; moneyAccumulated_ = 0;
                                               betCount_ = 0; passCount_ = 0;}
    private:
    uint32_t betAmmount_;
    std::string nickName_;
    int balance_;
    int moneyAccumulated_;
    uint32_t betCount_;
    uint32_t passCount_;
};