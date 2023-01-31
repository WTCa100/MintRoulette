#include "../include/Ai.h"

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