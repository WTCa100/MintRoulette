#pragma once

#include <cstdint>

#include "./Player.h"
#include "../../utilities/include/InputValidator.h"
#include "../../utilities/include/DebugLogger.h"


enum BetType{
    Pass = -1,
    StraightUp = 1,
    DozenBet = 2,
    EvenOdd = 3
};


enum GuessedNumberRangeType{
    LowerRange = 1,
    MiddleRange = 2,
    UpperRange = 3
};

class Bet : public ValidateInput
{
    public:
    // The following code is enum-like version of predefined winning odds.
    const double PassOdd = -1.0;
    const double StraightUpOdd = 0.028; // Equal to 1/35
    const double DozenBetOdd = 0.333; // Equal to 1/3
    const double EvenOddOdd = 0.5; // Equal to 1/2

    void askForBetType();
    void Pass();
    void buildBet(const Player& whoPlacedBet);
    void askStraightUp();
    void askDozenBet();
    void askEvenOdd();
    void askForBetAmmount(const Player& whoPlacedBet);

    bool isStringValid(const std::string& userInput) override;

    // Setters
    void setCurrentTurnPlayer(const Player& currentTurnPlayer) { currentTurnPlayer_ = currentTurnPlayer;}
    void setBetSucces(const bool& wasBetSuccesful) {wasBetSuccesful_ = wasBetSuccesful;}
    void setBetType(const BetType& betType) {betType_ = betType;}
    void setAmmountBetted(const int& ammountBetted) {ammountBetted_ = ammountBetted;}
    void setWinningOdds(const double& winningOdds) {winningOdds_ = winningOdds;}
    void setGuessedNumber(const size_t& guessedNumber) {guessedNumber_ = guessedNumber;}
    void setGuessedNumberRangeType(const GuessedNumberRangeType& guessedNumberRange) {GuessedNumberRange_ = guessedNumberRange;}
    void setIsOddChoosen(const bool& isOddChoosen) {isOddChoosen_ = isOddChoosen;}

    // Getters
    const double getWinningOdds() {return winningOdds_;}
    const bool getBetSucces() {return wasBetSuccesful_;}
    const BetType getBetType() { return betType_;} 
    const int getAmmountBetted() {return ammountBetted_;}
    const size_t getGuessedNumber() {return guessedNumber_;}
    const GuessedNumberRangeType getGuessedNumberRange() {return GuessedNumberRange_;}
    const bool getIsOddChoosen() {return isOddChoosen_;}

    Bet(DebugLogger* dbLog) : dbLog_(dbLog) { dbLog_->addDebugLog({dbLog_->dbLogClassBetInitialize}); }
    // Passing constructor
    Bet(const Player& currentTurnPlayer, DebugLogger* dbLog);
    private:
    DebugLogger* dbLog_;
    int ammountBetted_;
    size_t guessedNumber_;
    GuessedNumberRangeType GuessedNumberRange_;
    bool isOddChoosen_;
    BetType betType_;
    double winningOdds_;
    bool wasBetSuccesful_;
    Player currentTurnPlayer_;

};