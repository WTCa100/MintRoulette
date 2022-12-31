#pragma once

#include <string>

class Player
{
    public:
    
    void setNickName(const std::string& nickName) { nickName_ = nickName;}
    void setBalance(const int& balance) { balance_ = balance;}

    Player() = default;
    Player(int balance) {balance_ = balance;}
    Player(std::string nickName, int balance) {nickName_ = nickName; balance_ = balance;}
    private:
    std::string nickName_;
    int balance_;

};