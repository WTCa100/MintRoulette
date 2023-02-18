#include "../include/Ai.h"
#include "../../utilities/include/Paths.h"
#include "../../utilities/include/DebugLogger.h"

#include <vector>
#include <iostream>

/// @brief 
/// @return 0 - pass, 1 - bet
bool Ai::chooseActionBetOrPass()
{

    dbLog_->addDebugLog(
        {dbLog_->dbLogGameTurnBetAiChooseActionWithBalance(self_->getBalance())}
    );

    dbLog_->buildDebugLogs();

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
        // 50/50 ratio
        return actionSeed_ % 100 <= 50;
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

    return static_cast<uint32_t> (rand() % seedRoot);
}

Bet* Ai::buildBet(Bet*& botBet)
{
    botBet->setAmmountBetted(chooseBetSize(self_->getBalance()));
    botBet->setBetType(chooseBetType());
    dbLog_->addDebugLog(
        {dbLog_->dbLogGameTurnBetBuildSetAmmountBetted(botBet->getAmmountBetted())}
    );

    switch (botBet->getBetType())
    {
    case BetType::StraightUp:
        botBet->setGuessedNumber(chooseLuckynumber());
        botBet->setWinningOdds(botBet->StraightUpOdd);

        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnBetBuildSetBetType("StraightUp"),
             dbLog_->dbLogGameTurnBetBuildBetTypeWinningOdds("StraightUpOdd", botBet->getWinningOdds())}
        );


        break;
    case BetType::DozenBet:
        botBet->setGuessedNumberRangeType(chooseLuckyNumberRange());
        botBet->setWinningOdds(botBet->DozenBetOdd);

        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnBetBuildSetBetType("DozenBet"),
             dbLog_->dbLogGameTurnBetBuildBetTypeWinningOdds("StraightUpOdd", botBet->getWinningOdds())}
        );

        break;
    case BetType::EvenOdd:
        botBet->setIsOddChoosen(chooseOddOrEven());
        botBet->setWinningOdds(botBet->EvenOddOdd);

        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnBetBuildSetBetType("EvenOdd"),
             dbLog_->dbLogGameTurnBetBuildBetTypeWinningOdds("StraightUpOdd", botBet->getWinningOdds())}
        );

        break;
    default:
        break;
    }

    dbLog_->buildDebugLogs();

    return botBet;
}

Ai::Ai(Player* self, DebugLogger* dbLog)
{
    dbLog_ = dbLog;


    self_ = self;
    actionSeed_ = generateActionSeed();

    dbLog_->addDebugLog(
        {dbLog_->dbLogClassAiInitialize,
         dbLog_->dbLogGameTurnBetAiGeneratedSeed(actionSeed_)}
    );

    dbLog_->buildDebugLogs();
}

Ai::~Ai()
{
    dbLog_->addDebugLog(
        {dbLog_->dbLogClassAiDestruct}
    );

    dbLog_->buildDebugLogs();

}