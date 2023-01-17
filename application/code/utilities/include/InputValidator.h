#pragma once
#include <string>
#include <vector>

#include "../../game/include/Player.h"

class ValidateInput
{
    public:
    static bool isStringNumber(const std::string& userInput);
    virtual bool isStringValid(const std::string& userInput) {return userInput.empty();}
    static bool isADuplicatePlayer(const std::vector<Player*>& userInputs, const std::string targetUserInput);
    static std::string stringToLower(const std::string& makeLower);
};