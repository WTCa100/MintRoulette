#pragma once

#include <string>
#include <vector>

// Get Header
#include "./Player.h"
#include "./Bet.h"
#include "../../utilities/include/FileManager.h"

/// @brief Ai class contains every action that the user could have taken during a game
/// but picked as a random by an Ai.
/// @todo Make this class non-statci with more complexity
class Ai
{
    public:
    uint32_t generateActionSeed();
    bool chooseActionBetOrPass();
    bool chooseGoAllIn();
    BetType chooseBetType();
    int chooseLuckynumber();
    GuessedNumberRangeType chooseLuckyNumberRange();
    bool chooseOddOrEven();
    int chooseBetSize(int botBalance);
    static std::string pickBotName(FileManager* fManager);
    Bet* buildBet(Bet*& botBet);
   int generateSeed(int botBalance);


    // Setters
    void setInitialBankBalance(int* initialBankBalance) {initialBankBalance_ = initialBankBalance;}
    // Getters
    int* getInitialBankBalance() {return initialBankBalance_;}

    Ai(Player* self, DebugLogger* dbLog);
    ~Ai();

   /*Draft
   /// @brief This function generates seed that is core to decision making in Ai 
   /// @param botBalance is used as reference on what action should be done 
   /// @return Seed */
   private:
   DebugLogger* dbgLog_;
   uint32_t actionSeed_;
   Player* self_;
   int* initialBankBalance_;
};