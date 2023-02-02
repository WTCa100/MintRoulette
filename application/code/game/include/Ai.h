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
    static bool chooseActionBetOrPass();
    static BetType chooseBetType();
    static int chooseLuckynumber();
    static GuessedNumberRangeType chooseLuckyNumberRange();
    static bool chooseOddOrEven();
    static int chooseBetSize(int botBalance);
    static std::string pickBotName(FileManager* fManager /*This will be implemented later on in non-static version of the class*/);


    Ai(FileManager* fManager);

   /*Draft
   /// @brief This function generates seed that is core to decision making in Ai 
   /// @param botBalance is used as reference on what action should be done 
   /// @return Seed */
   int generateSeed(int botBalance);
   private:
   uint32_t actionSeed;
   Bet botsBet;
   FileManager* fManager;
};