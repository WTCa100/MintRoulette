#include <iostream>

#include "../include/InputValidator.h"
#include "../../utilities/include/InputValidator.h"

bool ValidateInput::isStringNumber(const std::string& userInput)
{
    if(userInput.empty())
    {
        // Todo implement exeption throws
        std::cout << "Your input cannot be empty!\n";
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