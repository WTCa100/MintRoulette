#pragma once

#include <cstdint>
#include "./Player.h"

enum BetType{
    StraightUp = 1,
    DozenBet = 2,
    EvenOdd = 3
};

class Bet
{
    public:
    void askForBetType(const Player& whoPlacedBet);
    void pass();
    void buildBet(const BetType& betType, int ammount);


    // Setters
    void setBetSucces(const bool& wasBetSuccesful) {wasBetSuccesful_ = wasBetSuccesful;}
    void setBetType(const BetType& betType) {betType_ = betType;}

    // Passing constructor
    Bet() = default;
    Bet(const Player& currentTurnPlayer);
    private:
    BetType betType_;
    bool wasBetSuccesful_;
    Player currentTurnPlayer_;

};