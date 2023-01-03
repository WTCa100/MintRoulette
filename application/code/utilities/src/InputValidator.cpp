#include <iostream>

#include "../include/InputValidator.h"
#include "../../utilities/include/InputValidator.h"

bool ValidateInput::isStringNumber(const std::string& userInput)
{
    if(userInput.empty())
    {
        return false;
    }
    
    for(auto i : userInput)
    {
        if(!isdigit(i))
        {
            return false;
        }
    }
    return true;
}

bool ValidateInput::isADuplicatePlayer(const std::vector<Player*>& userInputs, const std::string targetUserInput)
{
    for(auto i : userInputs)
    {
        if(i->getNickName() == targetUserInput)
        {
            return true;
        }
    }
    return false;
}