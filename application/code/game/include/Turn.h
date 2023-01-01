#pragma once

#include <string>
#include <vector>
#include <map>

#include "./Player.h"

class Turn
{
    public:
    uint16_t rollTheRoulette();
    void setLuckyNumber(const uint16_t& luckyNumber) {luckyNumber_ = luckyNumber;}
    void bettingPhase();
    void playTurn();

    Turn(std::vector<Player*>& currentPlayers, const uint32_t turnNumber) 
         :currentPlayers_(currentPlayers), turnNumber_(turnNumber) {}
    ~Turn();
    
    private:
    std::map<Player*, int> playerAndBets_;
    std::vector<Player*> currentPlayers_;
    uint16_t luckyNumber_;
    uint32_t turnNumber_;

};