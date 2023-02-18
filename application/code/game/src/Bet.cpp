#include <string>
#include <iostream>

#include "../include/Bet.h"
#include "../../utilities/include/InputValidator.h"
#include "../../utilities/include/MaxValues.h"

/// @brief Asks player to select desired bet type
void Bet::askForBetType()
{

    dbLog_->addDebugLog(
        {dbLog_->dbLogGameTurnBetBuildObtainBetType}
    );

    dbLog_->buildDebugLogs();

    std::string userInput;
    do
    {
        std::cout << "Bet types are:\n";
        std::cout << "1. Straight Up - you may pick one number\n";
        std::cout << "2. Dozen Bet - you may range withing the lucky number might be\n";
        std::cout << "3. Even odd - you may guess whether the lucky number is odd or even\n";

        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnBetBuildGetInput}
        );

        do
        {
            std::getline(std::cin, userInput);
            if(!ValidateInput::isStringNumber(userInput))
            {
                dbLog_->addDebugLog(
                    {dbLog_->dbLogGameTurnBetBuildGetInputResult(userInput, ValidateInput::isStringNumber(userInput))}
                );

                std::cout << "You may only enter a numberic value\n!";
            }
        } while (!ValidateInput::isStringNumber(userInput));

        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnBetBuildGetInputResult(userInput, ValidateInput::isStringNumber(userInput))}
        );

        switch (std::stoi(userInput))
        {
        case BetType::StraightUp:
            betType_ = BetType::StraightUp;            
            winningOdds_ = StraightUpOdd;

            dbLog_->addDebugLog(
                {dbLog_->dbLogGameTurnBetBuildSetBetType("StraightUp"),
                 dbLog_->dbLogGameTurnBetBuildBetTypeWinningOdds("StraightUp", winningOdds_)}
            );
            
            break;
        case BetType::DozenBet:
            betType_ = BetType::DozenBet;
            winningOdds_ = DozenBetOdd;

            dbLog_->addDebugLog(
                {dbLog_->dbLogGameTurnBetBuildSetBetType("DozenBet"),
                 dbLog_->dbLogGameTurnBetBuildBetTypeWinningOdds("DozenBet", winningOdds_)}
            );

            break;
        case BetType::EvenOdd:
            betType_ = BetType::EvenOdd;
            winningOdds_ = EvenOddOdd;

            dbLog_->addDebugLog(
                {dbLog_->dbLogGameTurnBetBuildSetBetType("EvenOdd"),
                 dbLog_->dbLogGameTurnBetBuildBetTypeWinningOdds("EvenOdd", winningOdds_)}
            );

            break;
        default:
            std::cout << "No such bet type!\n";
            break;
        }

        dbLog_->buildDebugLogs();

    } while (std::stoi(userInput) < 1 || std::stoi(userInput) > static_cast<int>(BetType::EvenOdd));



}

/// @brief Asks player how much money he want to bet from his bank
/// @param whoPlacedBet value of bet
/// @warning Bet cannot be greater than bank account.
void Bet::askForBetAmmount(const Player& whoPlacedBet)
{
    std::string* userInput = new std::string;
    std::cout << "How much money you are willing to bet? (you have "<< whoPlacedBet.getBalance() << " money)\n";
    do
    {
        do
        {
            std::getline(std::cin, *userInput);

            dbLog_->addDebugLog(
                {dbLog_->dbLogGameTurnGetInput}
            );

            if(!ValidateInput::isStringNumber(*userInput))
            {
                dbLog_->addDebugLog(
                    {dbLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
                );

                std::cout << "You may only place postivie numeric values\n";
            }
            } while (!ValidateInput::isStringNumber(*userInput));
            if(std::stoi(*userInput) > whoPlacedBet.getBalance())
            {
                std::cout << "You cannot bet more money than you have\n";
                dbLog_->addDebugLog(
                    {dbLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
                );                
            }
    } while (std::stoi(*userInput) > whoPlacedBet.getBalance());

    dbLog_->addDebugLog(
        {dbLog_->dbLogGameTurnBetBuildSetAmmountBetted(std::stoi(*userInput))}
    );

    dbLog_->buildDebugLogs();
    
    ammountBetted_ = std::stoi(*userInput);
    delete userInput;
}

/// @brief Sets up class attributes via askForBetAmmount, -Type and more specific 
/// information depending on bet type player choose
/// @param whoPlacedBet current Player 
void Bet::buildBet(const Player& whoPlacedBet)
{

    dbLog_->addDebugLog(
        {dbLog_->dbLogGaneTurnBetBetBuild}
    );

    dbLog_->buildDebugLogs();

    askForBetAmmount(whoPlacedBet);
    askForBetType();

    dbLog_->addDebugLog(
        {dbLog_->dbLogGameTurnBetGetDetails}
    );

    dbLog_->buildDebugLogs();

    switch (betType_)
    {
    case BetType::StraightUp:
        askStraightUp();
        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnBetBuildBetStraightUpSet(whoPlacedBet.getNickName(), guessedNumber_)}
        );

        break;
    case BetType::DozenBet:
        askDozenBet();

        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnBetBuildBetDozenSet(whoPlacedBet.getNickName(), std::to_string(static_cast<int>(betType_)))}
        );

        break;
    case BetType::EvenOdd:
        askEvenOdd();

        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnBetBuildBetIsOddChoosenSet(whoPlacedBet.getNickName(), isOddChoosen_ )}
        );

        break;
    default:
        std::cout << "Cannot place bet of unknown type!\n";
        break;
    }

}

/// @brief Builds straightUp type of bet
void Bet::askStraightUp()
{

    std::string* userInput = new std::string;
    std::cout << "Choose your lucky number guess (pick from 0 to 36)\n";
    do
    {

        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnBetBuildGetInput}
        );

        do
        {
            std::getline(std::cin, *userInput);
            if(!ValidateInput::isStringNumber(*userInput))
            {
                std::cout << "You may only place postivie numeric values\n";

                dbLog_->addDebugLog(
                    {dbLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
                );
            }           

        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
        );


        } while (!ValidateInput::isStringNumber(*userInput));
        
        if(std::stoi(*userInput) > MAX_POSSIBLE_LUCKY_NUMBER)
        {
            std::cout << "Your entry cannot be greater than " << MAX_POSSIBLE_LUCKY_NUMBER << std::endl;            
        }

        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
        );

        dbLog_->buildDebugLogs();
    } while (std::stoi(*userInput) > MAX_POSSIBLE_LUCKY_NUMBER);
    guessedNumber_ = std::stoi(*userInput);
    delete userInput;
}

/// @brief Builds dozen type of bet
void Bet::askDozenBet()
{

    std::string* userInput = new std::string;
    std::cout << "Choose the range with the lucky number.\n";
    std::cout << "1. 1 - 12\n";
    std::cout << "2. 13 - 24\n";
    std::cout << "3. 25 - 36\n";
    do
    {

        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnBetBuildGetInput}
        );

        do
        {
            std::getline(std::cin, *userInput);
            if(!ValidateInput::isStringNumber(*userInput))
            {
                std::cout << "Please enter a numeric value only\n";
                dbLog_->addDebugLog(
                    {dbLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
                );                
            }
        } while (!ValidateInput::isStringNumber(*userInput));
        if(std::stoi(*userInput) < 1 || std::stoi(*userInput) > 3)
        {
            std::cout << "Plase enter values within range 1 to 3\n";
            dbLog_->addDebugLog(
                {dbLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
            );                   
        }
    } while (std::stoi(*userInput) < 1 || std::stoi(*userInput) > 3);

    GuessedNumberRange_ = static_cast<GuessedNumberRangeType>(std::stoi(*userInput));

    delete userInput;
}

/// @brief Builds Odd/Even type of bet.
void Bet::askEvenOdd()
{

    dbLog_->addDebugLog(
        {dbLog_->dbLogGameTurnBetBuildGetInput}
    );

    std::string* userInput = new std::string;
    std::cout << "Is lucky number odd or even?\n";
    do
    {
        std::getline(std::cin, *userInput);
        if(!Bet::isStringValid(*userInput))
        {
            std::cout << "It's either odd or even\n";

            dbLog_->addDebugLog(
                {dbLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, Bet::isStringValid(*userInput))}
            );

        }
    } while (!Bet::isStringValid(*userInput));

    // Standarize input
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

/// @brief Checks if player have inputed "odd" or "even"
/// @param userInput user specified string value
/// @return if input is "odd" or "even"
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

/// @brief This function displays that player has passed his turn
void Bet::Pass()
{

    dbLog_->addDebugLog(
        {dbLog_->dbLogGameTurnBetPlayerPassed(currentTurnPlayer_.getNickName())}
    );

    std::cout << currentTurnPlayer_.getNickName() << " - has Pass this turn!\n";
}

/// @brief Passing constructor
/// @param currentTurnPlayer 
Bet::Bet(const Player& currentTurnPlayer, DebugLogger* dbLog)
{   
    dbLog_ = dbLog;

    dbLog_->addDebugLog(
        {dbLog_->dbLogClassBetInitialize}
    );

    dbLog->buildDebugLogs();

    currentTurnPlayer_ = currentTurnPlayer;
    betType_ = BetType::Pass;
    winningOdds_ = -1.0;
    ammountBetted_ = 0;
    Pass();
}