#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "./Player.h"
#include "./Bet.h"
#include "../../utilities/include/Logger.h"
#include "../../utilities/include/DebugLogger.h"

class Turn
{
    public:
    uint16_t randomizeNumber();
    void bettingPhase();
    void playTurn();
    void rollTheRoulette();
    void summaryPhase();
    // If false is returned the player will Pass
    bool askForBet();


    // Setters
    void setLuckyNumber(const uint16_t& luckyNumber) {luckyNumber_ = luckyNumber;}

    // Getter
    std::unordered_map<Player*, Bet*> getPlayersBets() {return playerAndBets_; }

    Turn(std::vector<Player*>& currentPlayers, const uint32_t turnNumber, Logger* gameLog, DebugLogger* dbLog) 
         :currentPlayers_(currentPlayers), turnNumber_(turnNumber), gameLog_(gameLog), dbLog_(dbLog) { dbLog_->addDebugLog({dbLog_->dbLogClassTurnInitialize}); }
    ~Turn();
    
    private:
    // Map with turn id as a key, and player with his bets as values
    DebugLogger* dbLog_;
    Logger* gameLog_;
    std::unordered_map<Player*, Bet*> playerAndBets_;
    std::vector<Player*> currentPlayers_;
    uint16_t luckyNumber_;
    uint32_t turnNumber_;

};