#pragma once

#include <string>

class Player
{
    public:
    void displayMoneyWonLoss();
    void displayBetPassCounts();
    void moveToGlobalStats();

    // Setters
    // Locals
    void setBalance(const int& balance) { balance_ = balance;}
    void setMoneyAccumulated(const int& moneyAccumulated) {moneyAccumulated_ = moneyAccumulated;}
    void setGoodBetCount(const uint32_t& goodBetCount) {goodBetCount_ = goodBetCount;}
    void setBetCount(const uint32_t& betCount) {betCount_ = betCount;}
    void setPassCount(const uint32_t& passCount) {passCount_ = passCount;}
    // Globals
    void setNickName(const std::string& nickName) { nickName_ = nickName;}
    void setGlobalMoneyAccumulated(const int& globMoneyAccumulated) {globMoneyAccumulated_ = globMoneyAccumulated;}
    void setGlobalGoodBetCount(const uint32_t& globGoodBetCount) {globGoodBetCount_ = globGoodBetCount;}
    void setGlobalBetCount(const uint32_t& globBetCount) {globBetCount_ = globBetCount;}
    void setGlobalPassCount(const uint32_t& globPassCount) {globPassCount_ = globPassCount;}

    // Getters
    // Locals
    int getBalance() const {return balance_;}
    int getMoneyAccumulated() const {return moneyAccumulated_;}
    uint32_t getGoodBetCount() const {return goodBetCount_;}
    uint32_t getBetCount() const {return betCount_;}
    uint32_t getPassCount() const {return passCount_;}
    // Globals
    std::string getNickName() const {return nickName_;}
    int getGlobalMoneyAccumulated() const {return globMoneyAccumulated_;}
    uint32_t getGlobalGoodBetCount() const {return globGoodBetCount_;}
    uint32_t getGlobalBetCount() const {return globBetCount_;}
    uint32_t getGlobalPassCount() const {return globPassCount_;}

    Player() = default;
    Player(int balance);
    Player(const std::string nickName, int balance);                                    
    Player(const std::string nickName, int globMoneyAccumulated, uint32_t goodBetCount, uint32_t betCount,
           uint32_t passCount, int balance = 0);

    private:
    // Local variables related to one session
    int balance_;
    int moneyAccumulated_;
    uint32_t goodBetCount_;
    uint32_t betCount_;
    uint32_t passCount_;

    // Global variables
    std::string nickName_;
    int globMoneyAccumulated_;
    uint32_t globGoodBetCount_;
    uint32_t globBetCount_;
    uint32_t globPassCount_;

};