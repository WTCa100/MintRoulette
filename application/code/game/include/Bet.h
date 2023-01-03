#pragma once

#include <cstdint>

#include "./Player.h"
#include "../../utilities/include/InputValidator.h"

enum BetType{
    StraightUp = 1,
    DozenBet = 2,
    EvenOdd = 3
};

enum guessedNumberRangeType{
    LowerRange = 1,
    MiddleRange = 2,
    UpperRange = 3
};

class Bet : public ValidateInput
{
    public:
    void askForBetType();
    void pass();
    void buildBet(const Player& whoPlacedBet);
    void askStraightUp();
    void askDozenBet();
    void askEvenOdd();

    bool isStringValid(const std::string& userInput) override;

    // Setters
    void setCurrentTurnPlayer(const Player& currentTurnPlayer) { currentTurnPlayer_ = currentTurnPlayer;}
    void setBetSucces(const bool& wasBetSuccesful) {wasBetSuccesful_ = wasBetSuccesful;}
    void setBetType(const BetType& betType) {betType_ = betType;}
    void setAmmountBetted(const int& ammountBetted) {ammountBetted_ = ammountBetted;}

    // Getter
    const BetType getBetType() { return betType_;}
    const int getAmmountBetted() {return ammountBetted_;}
    const size_t getGuessedNumber() {return guessedNumber_;}
    const size_t getGuessedNumberRange() {return guessedNumberRangeType_;}
    const bool getIsOdChoosen() {return isOddChoosen_;}

    Bet() = default;
    // Passing constructor
    Bet(const Player& currentTurnPlayer);
    private:
    int ammountBetted_;
    size_t guessedNumber_;
    //TODO change to different type: guessedNumberRangeType
    size_t guessedNumberRangeType_;
    bool isOddChoosen_;
    BetType betType_;
    bool wasBetSuccesful_;
    Player currentTurnPlayer_;

};