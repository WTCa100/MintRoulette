#include "../include/Ai.h"
#include "../../utilities/include/Paths.h"

#include <vector>

/// @brief 
/// @return 0 - pass, 1 - bet
bool Ai::chooseActionBetOrPass()
{
    return static_cast<bool>(rand() % 2);
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

int Ai::chooseBetSize(int botBalance)
{
    return rand() % botBalance + 1;
}

std::string Ai::pickBotName(FileManager* fManager)
{
    std::vector<std::string> names = fManager->makeFileContentUnique(fManager->loadFileContent(FILE_GAME_AI_NAME_LIST_PATH, FILE_AI_NAME_LIST));
    return names[rand() % names.size()];
}

Ai::Ai(FileManager* fManager, Player* self)
{
    fManager_ = fManager;
    self_ = self;
}

uint32_t Ai::generateActionSeed()
{
    int seedRoot = self_->getBalance();

    actionSeed_ = rand() % seedRoot;

}