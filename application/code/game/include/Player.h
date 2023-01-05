#pragma once

#include <string>

class Player
{
    public:
    void displayMoneyWonLoss();

    // Setters
    void setNickName(const std::string& nickName) { nickName_ = nickName;}
    void setBalance(const int& balance) { balance_ = balance;}
    void setMoneyAccumulated(const int& moneyAccumulated) {moneyAccumulated_ = moneyAccumulated;}
    void setBetAmmount(const uint32_t& betAmmount) {betAmmount_ = betAmmount;}

    // Getters
    std::string getNickName() const {return nickName_;}
    int getBalance() const {return balance_;}
    int getMoneyAccumulated() const {return moneyAccumulated_;}

    Player() = default;
    Player(int balance) {balance_ = balance; moneyAccumulated_ = 0;}
    Player(std::string nickName, int balance) {nickName_ = nickName; balance_ = balance; moneyAccumulated_ = 0;}
    private:
    uint32_t betAmmount_;
    std::string nickName_;
    int balance_;
    int moneyAccumulated_;

};