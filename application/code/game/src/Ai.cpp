#include "../include/Ai.h"
#include "../../utilities/include/Paths.h"
#include "../../utilities/include/DebugLogger.h"

#include <vector>
#include <iostream>

/// @brief 
/// @return 0 - pass, 1 - bet
bool Ai::chooseActionBetOrPass()
{

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameTurnBetAiChooseActionWithBalance(self_->getBalance())}
    );

    dbgLog_->buildDebugLogs();

    // Bot shall choose depending on ammount of money he has wether pass or not
    // First let's check ammount of money player have (it's fixed since it will make the game flow much faster)
    // This will determine the highest odds
    if(self_->getBalance() > 1500)
    {
        // Now depending on ability to modulate balance we will determine if player want to bet or not
        // Fist case will have ratio 80% for bet and 20% for pass
        return actionSeed_ % 100 <= 80;
    }
    else if(self_->getBalance() > 150 && self_->getBalance() <= 1500)
    {
        // Originally 50/50 ratio was here, however that still felt too safe for bots
        return actionSeed_ % 100 <= 35;
    }
    else
    {
        // 20% for bet and 80% for pass.
        // Use addition to actionSeed_ since actionSeed_ might be actually lower than 100, because it's based on player balance.
        // It is possible that if we leave actionSeed_ % 100 <= 20, that it will stuck on pass when for player balance will be lower than 20.
        // Thus we have to add certain components to the action generation to make it work as intended.
        return (rand() % actionSeed_ + rand() % 900 + 101) % 100 <= 20;
    }
    
    // Make sure we return something even if none of the condisions are met
    std::cout << "Some error occured!\n";
    return 0;
}

BetType Ai::chooseBetType()
{
    return static_cast<BetType>(rand() % 3 + 1);
}

int Ai::chooseLuckynumber()
{
    return rand() % 37;
}

GuessedNumberRangeType Ai::chooseLuckyNumberRange()
{
    return static_cast<GuessedNumberRangeType>(rand() % 3 + 1);
}

/// @brief 
/// @return 0 - even, 1 - odd 
bool Ai::chooseOddOrEven()
{
    return static_cast<bool>(rand() % 2);
}


bool Ai::chooseGoAllIn()
{
    if(actionSeed_ % 7 == 0 || actionSeed_ % 13 == 0)
    {
        return true;
    }
    return false;
}

int Ai::chooseBetSize(int botBalance)
{   
    if(self_->getBalance() > 150)
    {
        if(chooseGoAllIn())
        {
            return self_->getBalance();
        }
    }
    return rand() % (botBalance - (botBalance/10)) + 1;
}

std::string Ai::pickBotName(FileManager* fManager)
{
    std::vector<std::string> names = fManager->makeFileContentUnique(fManager->loadFileContent(FILE_GAME_AI_NAME_LIST_PATH, FILE_AI_NAME_LIST));
    return names[rand() % names.size()];
}

uint32_t Ai::generateActionSeed()
{
    int seedRoot = self_->getBalance();
    int actionSeed = rand() % seedRoot;
    if(actionSeed)
    {
        return actionSeed;
    }
    else
    {
        return 1;
    }
}

Bet* Ai::buildBet(Bet*& botBet)
{
    botBet->setAmmountBetted(chooseBetSize(self_->getBalance()));
    botBet->setBetType(chooseBetType());
    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameTurnBetBuildSetAmmountBetted(botBet->getAmmountBetted())}
    );

    switch (botBet->getBetType())
    {
    case BetType::StraightUp:
        botBet->setGuessedNumber(chooseLuckynumber());
        botBet->setWinningOdds(botBet->StraightUpOdd);

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnBetBuildSetBetType("StraightUp"),
             dbgLog_->dbLogGameTurnBetBuildBetTypeWinningOdds("StraightUpOdd", botBet->getWinningOdds())}
        );


        break;
    case BetType::DozenBet:
        botBet->setGuessedNumberRangeType(chooseLuckyNumberRange());
        botBet->setWinningOdds(botBet->DozenBetOdd);

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnBetBuildSetBetType("DozenBet"),
             dbgLog_->dbLogGameTurnBetBuildBetTypeWinningOdds("StraightUpOdd", botBet->getWinningOdds())}
        );

        break;
    case BetType::EvenOdd:
        botBet->setIsOddChoosen(chooseOddOrEven());
        botBet->setWinningOdds(botBet->EvenOddOdd);

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnBetBuildSetBetType("EvenOdd"),
             dbgLog_->dbLogGameTurnBetBuildBetTypeWinningOdds("StraightUpOdd", botBet->getWinningOdds())}
        );

        break;
    default:
        break;
    }

    dbgLog_->buildDebugLogs();

    return botBet;
}

Ai::Ai(Player* self, DebugLogger* dbLog)
{
    dbgLog_ = dbLog;


    self_ = self;
    actionSeed_ = generateActionSeed();

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogClassAiInitialize,
         dbgLog_->dbLogGameTurnBetAiGeneratedSeed(actionSeed_)}
    );

    dbgLog_->buildDebugLogs();
}

Ai::~Ai()
{
    dbgLog_->addDebugLog(
        {dbgLog_->dbLogClassAiDestruct}
    );

    dbgLog_->buildDebugLogs();

}