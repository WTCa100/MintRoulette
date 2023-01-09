#include <string>
#include <iostream>

#include "../include/Bet.h"
#include "../../utilities/include/InputValidator.h"
#include "../../utilities/include/MaxValues.h"

void Bet::askForBetType()
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
            betType_ = BetType::StraightUp;
            winningOdds_ = StraightUpOdd;
            break;
        case BetType::DozenBet:
            betType_ = BetType::DozenBet;
            winningOdds_ = DozenBetOdd;
            break;
        case BetType::EvenOdd:
            betType_ = BetType::EvenOdd;
            winningOdds_ = EvenOddOdd;
            break;
        default:
            std::cout << "No such bet type!\n";
            break;
        }
        printf("Debug Info: Bet: WinningOdds: Value: %.3f\n", winningOdds_);
    } while (std::stoi(userInput) < 1 || std::stoi(userInput) > static_cast<int>(BetType::EvenOdd));
}

void Bet::askForBetAmmount(const Player& whoPlacedBet)
{
    std::string* userInput = new std::string;
    std::cout << "How much money you are willing to bet? (you have "<< whoPlacedBet.getBalance() << "\n";
    do
    {
        do
        {
        std::getline(std::cin, *userInput);
        if(!ValidateInput::isStringNumber(*userInput))
        {
            std::cout << "You may only place postivie numeric values\n";
        }
        } while (!ValidateInput::isStringNumber(*userInput));
        if(std::stoi(*userInput) > whoPlacedBet.getBalance())
        {
            std::cout << "You cannot bet more money than you have\n";
        }
    } while (std::stoi(*userInput) > whoPlacedBet.getBalance());
    ammountBetted_ = std::stoi(*userInput);
    delete userInput;
}

void Bet::buildBet(const Player& whoPlacedBet)
{
    askForBetAmmount(whoPlacedBet);
    askForBetType();
    switch (betType_)
    {
    case BetType::StraightUp:
        askStraightUp();
        break;
    case BetType::DozenBet:
        askDozenBet();
        break;
    case BetType::EvenOdd:
        askEvenOdd();
        break;
    default:
        std::cout << "Cannot place bet of unknown type!\n";
        break;
    }

}

void Bet::askStraightUp()
{
    std::string* userInput = new std::string;
    std::cout << "Choose your lucky number guess (pick from 0 to 36)\n";
    do
    {
        do
        {
            std::getline(std::cin, *userInput);
            if(!ValidateInput::isStringNumber(*userInput))
            {
                std::cout << "You may only place postivie numeric values\n";
            }           
        } while (!ValidateInput::isStringNumber(*userInput));
        
        if(std::stoi(*userInput) > MAX_POSSIBLE_LUCKY_NUMBER)
        {
            std::cout << "Your entry cannot be greater than " << MAX_POSSIBLE_LUCKY_NUMBER << std::endl;
        }
    } while (std::stoi(*userInput) > MAX_POSSIBLE_LUCKY_NUMBER);
    guessedNumber_ = std::stoi(*userInput);
    delete userInput;
}

void Bet::askDozenBet()
{
    std::string* userInput = new std::string;
    std::cout << "Choose the range with the lucky number.\n";
    std::cout << "1. 1 - 12\n";
    std::cout << "2. 13 - 24\n";
    std::cout << "3. 25 - 36\n";
    do
    {
        do
        {
            std::getline(std::cin, *userInput);
            if(!ValidateInput::isStringNumber(*userInput))
            {
                std::cout << "Please enter a numeric value only\n";
            }
        } while (!ValidateInput::isStringNumber(*userInput));
        if(std::stoi(*userInput) < 1 || std::stoi(*userInput) > 3)
        {
            std::cout << "Plase enter values within range 1 to 3\n";
        }
    } while (std::stoi(*userInput) < 1 || std::stoi(*userInput) > 3);
    GuessedNumberRange_ = static_cast<GuessedNumberRangeType>(std::stoi(*userInput));
    delete userInput;
}

void Bet::askEvenOdd()
{
    std::string* userInput = new std::string;
    std::cout << "Is lucky number odd or even?\n";
    do
    {
        std::getline(std::cin, *userInput);
        if(!Bet::isStringValid(*userInput))
        {
            std::cout << "It's either odd or even\n";
        }
    } while (!Bet::isStringValid(*userInput));
    for(auto& i : *userInput)
    {
        i = tolower(i);
    }
    if(*userInput == "odd")
    {
        isOddChoosen_ = true;
        delete userInput;
        return;
    }
    isOddChoosen_ = false;
    delete userInput;
}

bool Bet::isStringValid(const std::string& userInput)
{
    std::string* tmpHolder = new std::string(userInput);
    for(auto& i: *tmpHolder)
    {
        i = tolower(i);
    }
    if(*tmpHolder == "odd" || *tmpHolder == "even")
    {
        delete tmpHolder;
        return true;
    }
    delete tmpHolder;
    return false;
}

void Bet::Pass()
{
    std::cout << currentTurnPlayer_.getNickName() << " - has Pass this turn!\n";
}

Bet::Bet(const Player& currentTurnPlayer)
{
    currentTurnPlayer_ = currentTurnPlayer;
    betType_ = BetType::Pass;
    winningOdds_ = -1.0;
    ammountBetted_ = 0;
    Pass();
}