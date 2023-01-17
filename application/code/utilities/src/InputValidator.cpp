#include <iostream>

#include "../include/InputValidator.h"
#include "../../utilities/include/InputValidator.h"

/// @brief Checks if user input is a number
/// @param userInput provided input
/// @return is provided string is a number
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

/// @brief Checks if provided user input already exists
/// @param userInputs vector populated with all playeres
/// @param targetUserInput comparator
/// @return if another record with same value exists
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

std::string ValidateInput::stringToLower(const std::string& makeLower)
{
    std::string madeLowered;
    for(auto character : makeLower)
    {
        madeLowered += tolower(character);
    }
    return madeLowered;
}