#include <string>

#include "../include/Bet.h"
#include "../../utilities/include/InputValidator.h"

void Bet::betPlace(const Player& whoPlacedBet)
{
    std::string userInput;
    do
    {
        std::cout << "Bet types are:\n";
        std::cout << "1. Straight Up - you may pick one number\n";
        std::cout << "2. Dozen Bet - you may range withing the lucky number might be\n";
        std::cout << "3 Even odd - you may guess whether the lucky number is odd or even\n";
        do
        {
            std::getline(std::cin, userInput);
            if(!ValidateInput::isStringNumber(userInput))
            {
                std::cout << "You may only enter a numberic value\n!";
            }
        } while (!ValidateInput::isStringNumber(userInput));

        switch (std::stoi(userInput))
        {
        case BetType::StraightUp:
            setBetType(BetType::StraightUp);
            break;
        case BetType::DozenBet:
            setBetType(BetType::DozenBet);
            break;
        case BetType::EvenOdd:
            setBetType(BetType::EvenOdd);
            break;
        default:
            std::cout << "No such bet type!\n";
            break;
        }
    } while (std::stoi(userInput) < 1 || std::stoi(userInput) > static_cast<int>(BetType::EvenOdd));
    
    
}

void Bet::pass()
{
    std::cout << currentTurnPlayer_.getNickName() << " - has passed this turn!\n";
}

Bet::Bet(const Player& currentTurnPlayer)
{
    currentTurnPlayer_ = currentTurnPlayer;
    pass();
}