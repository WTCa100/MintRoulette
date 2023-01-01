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