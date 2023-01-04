#pragma once

#include <cstdint>

#include "./Player.h"
#include "../../utilities/include/InputValidator.h"

enum BetType{
    Pass = -1,
    StraightUp = 1,
    DozenBet = 2,
    EvenOdd = 3
};

// The following code is enum-like version of predefined winning odds.
constexpr double PassOdd = -1.0;
constexpr double StraightUpOdd = 0.028; // Equal to 1/35
constexpr double DozenBetOdd = 0.333; // Equal to 1/3
constexpr double EvenOddOdd = 0.5; // Equal to 1/2

enum GuessedNumberRangeType{
    LowerRange = 1,
    MiddleRange = 2,
    UpperRange = 3
};

class Bet : public ValidateInput
{
    public:
    void askForBetType();
    void Pass();
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
    void setWinningOdds(const double& winningOdds) {winningOdds_ = winningOdds;}

    // Getters
    const double getWinningOdds() {return winningOdds_;}
    const bool getBetSucces() {return wasBetSuccesful_;}
    const BetType getBetType() { return betType_;}
    const int getAmmountBetted() {return ammountBetted_;}
    const size_t getGuessedNumber() {return guessedNumber_;}
    const GuessedNumberRangeType getGuessedNumberRange() {return GuessedNumberRange_;}
    const bool getIsOddChoosen() {return isOddChoosen_;}

    Bet() = default;
    // Passing constructor
    Bet(const Player& currentTurnPlayer);
    private:
    int ammountBetted_;
    size_t guessedNumber_;
    GuessedNumberRangeType GuessedNumberRange_;
    bool isOddChoosen_;
    BetType betType_;
    double winningOdds_;
    bool wasBetSuccesful_;
    Player currentTurnPlayer_;

};