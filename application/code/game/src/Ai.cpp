#include "../include/Ai.h"
#include "../../utilities/include/Paths.h"

#include <vector>

/// @brief 
/// @return 0 - pass, 1 - bet
bool Ai::chooseActionBetOrPass()
{
    return chooseYesOrNo();
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
    return chooseYesOrNo();
}

bool Ai::chooseYesOrNo()
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
    std::cout << "Debug: Game: Ai: Seed: Show: " << actionSeed_ << std::endl;
    if(self_->getBalance() > 150)
    {
        if(chooseGoAllIn())
        {
            std::cout << "Debug: Game: Ai: Bet: Size: Msg: Go all in!\n";
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
    switch (botBet->getBetType())
    {
    case BetType::StraightUp:
        botBet->setGuessedNumber(chooseLuckynumber());
        botBet->setWinningOdds(botBet->StraightUpOdd);
        break;
    case BetType::DozenBet:
        botBet->setGuessedNumberRangeType(chooseLuckyNumberRange());
        botBet->setWinningOdds(botBet->DozenBetOdd);
        break;
    case BetType::EvenOdd:
        botBet->setIsOddChoosen(chooseOddOrEven());
        botBet->setWinningOdds(botBet->EvenOddOdd);
        break;
    default:
        break;
    }

    return botBet;
}

Ai::Ai(Player* self)
{
    self_ = self;

    actionSeed_ = generateActionSeed();
}