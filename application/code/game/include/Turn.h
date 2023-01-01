#pragma once

#include <string>
#include <vector>
#include <map>

#include "./Player.h"

class Turn
{
    public:
    uint16_t randomizeNumber();
    void bettingPhase();
    void playTurn();
    void rollTheRoulette();
    // If false is returned the player will pass
    bool askForBet();


    // Setters
    void setLuckyNumber(const uint16_t& luckyNumber) {luckyNumber_ = luckyNumber;}
    Turn(std::vector<Player*>& currentPlayers, const uint32_t turnNumber) 
         :currentPlayers_(currentPlayers), turnNumber_(turnNumber) {}
    ~Turn();
    
    private:
    std::map<Player*, int> playerAndBets_;
    std::vector<Player*> currentPlayers_;
    uint16_t luckyNumber_;
    uint32_t turnNumber_;

};