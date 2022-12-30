#pragma once

#include <string>

class Player
{
    public:
    
    void setNickName(std::string nickName);
    void setBalance(int balnce);

    private:
    std::string nickName_;
    int balance_;

};