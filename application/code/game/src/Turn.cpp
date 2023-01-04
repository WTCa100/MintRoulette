#include <iostream>
#include <windows.h>

// Get header
#include "../include/Turn.h"
#include "../include/Bet.h"
#include "../../utilities/include/MaxValues.h"

// Get source
#include "./Bet.cpp"

uint16_t Turn::randomizeNumber()
{
    return static_cast<uint16_t>(rand()% 37);
}

void Turn::bettingPhase()
{
    for(int i = 0; i < currentPlayers_.size(); i++)
    {
        std::cout << "Debug info: " << currentPlayers_[i]->getNickName() << " turn has started\n";
        std::cout << "It's " << currentPlayers_[i]->getNickName() << "'s turn\n";
        std::cout << "You have: " << currentPlayers_[i]->getBalance() << " worth of balance\n";
        // Aske player if he wants to bet
        if(askForBet())
        {
            Bet* playerBet = new Bet();
            playerBet->askForBetType();
            playerBet->buildBet(*currentPlayers_[i]);
            playerAndBets_.insert(std::make_pair(currentPlayers_[i], playerBet));
        }        
        else
        {
            Bet* playerPass = new Bet(*currentPlayers_[i]);
            playerAndBets_.insert(std::make_pair(currentPlayers_[i], playerPass));
        }
        
        std::cout << "Debug info: " << currentPlayers_[i]->getNickName() << " turn has ended\n";
    }
}

void Turn::rollTheRoulette()
{

    std::vector<uint16_t> numbers(3, 0);
    for(auto &i : numbers)
    {
        i = randomizeNumber();
    }
    size_t luckyNumPos = rand() % numbers.size();
    setLuckyNumber(numbers[luckyNumPos]);
    std::cout << "Bets are now clossed!\n";
    std::cout << "The roulette is being rolled\n";
    for(int i = 0; i < numbers.size(); i++)
    {
        std::cout << numbers[i] << "    ";
        Sleep(1000); 
    }
    std::cout << std::endl;
    std::cout << "The lucky number is: ";
    Sleep(1000);
    std::cout << luckyNumber_ << std::endl;

    // Set lucky number
    for(auto i : playerAndBets_)
    {
        // Todo set rest of BetTypes success
        switch (i.second->getBetType())
        {
        case BetType::StraightUp:
            i.second->setBetSucces(i.second->getGuessedNumber() == luckyNumber_);
            break;
        case BetType::DozenBet:
            switch(i.second->getGuessedNumberRange())
            {
                case guessedNumberRangeType::LowerRange:
                i.second->setBetSucces(luckyNumber_ >= MIN_LOWER_RANGE || luckyNumber_ <= MAX_LOWER_RANGE);
                break;
                case guessedNumberRangeType::MiddleRange:
                i.second->setBetSucces(luckyNumber_ >= MIN_MIDDLE_RANGE || luckyNumber_ <= MAX_MIDDLE_RANGE);
                break;
                case guessedNumberRangeType::UpperRange:
                i.second->setBetSucces(luckyNumber_ >= MIN_UPPER_RANGE || luckyNumber_ <= MAX_UPPER_RANGE);
                break;
            }
            break;
        case BetType::EvenOdd:
            if(i.second->getIsOddChoosen())
            {
                i.second->setBetSucces(luckyNumber_ % 2 != 0);
            }
            else
            {
                i.second->setBetSucces(luckyNumber_ % 2 == 0);
            }
            break;
        default:
            std::cout << "Debug Info: "<< i.first->getNickName() <<"passed this turn!\n";
            break;
        }
    }
}

bool Turn::askForBet()
{
    std::string userInput;
    std::cout << "Are you betting or passing?\n";
    do
    {
        "1. Yes\n";
        "2. No\n";
        do
        {
            std::getline(std::cin, userInput);
            if(!ValidateInput::isStringNumber(userInput))
            {
                std::cout << "You may enter only numeric value\n";
            }
        } while (!ValidateInput::isStringNumber(userInput));
        if(std::stoi(userInput) == 1)
        {
            return true;
        }
        else if(std::stoi(userInput) == 2)
        {
            return false;
        }
        else
        {
            std::cout << "It's either yes or no\n";
        }
    } while (!(std::stoi(userInput) == 1 || std::stoi(userInput) == 2));
    return false;
}

void Turn::summaryPhase()
{
    // Todo send message in summary 
    for(auto player : playerAndBets_)
    {
        std::cout << player.first->getNickName() << " ";
        switch (player.second->getBetType())
        {
        case BetType::StraightUp:
            std::cout << "betted straight up with " 
                      << player.second->getGuessedNumber();
            break;
        case BetType::DozenBet:
            break;
        case BetType::EvenOdd:
            break;
        default:
            std::cout << "passed this turn!\n";
            break;
        }
        if(!player.second->getBetType() == BetType::Pass)
        {
            if(player.second->getBetSucces())
            {
                std::cout << " and got it!\n";
                // Dummy value for now
                std::cout << player.first->getNickName() <<" won " << player.second->getAmmountBetted() <<"!\n";
            }
            else
            {
                std::cout << "and did not got it right!\n";
                std::cout << player.first->getNickName() <<" lost " << player.second->getAmmountBetted() <<"!\n";
            }
        }
    }
}

void Turn::playTurn()
{
    std::cout << "Turn " << turnNumber_ << std::endl;
    bettingPhase();
    rollTheRoulette();
    summaryPhase();
}

Turn::~Turn()
{
    std::cout << "End of turn: " << turnNumber_ << "!\n";
}