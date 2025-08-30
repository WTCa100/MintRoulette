#include <string>
#include <iostream>

#include "../include/Bet.h"
#include "../../utilities/include/InputValidator.h"
#include "../../utilities/include/MaxValues.h"

/// @brief Asks player to select desired bet type
void Bet::askForBetType()
{

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameTurnBetBuildObtainBetType}
    );

    dbgLog_->buildDebugLogs();

    std::string userInput;
    do
    {
        std::cout << "Bet types are:\n";
        std::cout << "1. Straight Up - you may pick one number\n";
        std::cout << "2. Dozen Bet - you may range withing the lucky number might be\n";
        std::cout << "3. Even odd - you may guess whether the lucky number is odd or even\n";

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnBetBuildGetInput}
        );

        do
        {
            std::getline(std::cin, userInput);
            if(!ValidateInput::isStringNumber(userInput))
            {
                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogGameTurnBetBuildGetInputResult(userInput, ValidateInput::isStringNumber(userInput))}
                );

                std::cout << "You may only enter a numberic value\n!";
            }
        } while (!ValidateInput::isStringNumber(userInput));

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnBetBuildGetInputResult(userInput, ValidateInput::isStringNumber(userInput))}
        );

        switch (std::stoi(userInput))
        {
        case BetType::StraightUp:
            betType_ = BetType::StraightUp;            
            winningOdds_ = StraightUpOdd;

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameTurnBetBuildSetBetType("StraightUp"),
                 dbgLog_->dbLogGameTurnBetBuildBetTypeWinningOdds("StraightUp", winningOdds_)}
            );
            
            break;
        case BetType::DozenBet:
            betType_ = BetType::DozenBet;
            winningOdds_ = DozenBetOdd;

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameTurnBetBuildSetBetType("DozenBet"),
                 dbgLog_->dbLogGameTurnBetBuildBetTypeWinningOdds("DozenBet", winningOdds_)}
            );

            break;
        case BetType::EvenOdd:
            betType_ = BetType::EvenOdd;
            winningOdds_ = EvenOddOdd;

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameTurnBetBuildSetBetType("EvenOdd"),
                 dbgLog_->dbLogGameTurnBetBuildBetTypeWinningOdds("EvenOdd", winningOdds_)}
            );

            break;
        default:
            std::cout << "No such bet type!\n";
            break;
        }

        dbgLog_->buildDebugLogs();

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

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameTurnGetInput}
            );

            if(!ValidateInput::isStringNumber(*userInput))
            {
                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
                );

                std::cout << "You may only place postivie numeric values\n";
            }
            } while (!ValidateInput::isStringNumber(*userInput));
            if(std::stoi(*userInput) > whoPlacedBet.getBalance())
            {
                std::cout << "You cannot bet more money than you have\n";
                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
                );                
            }
    } while (std::stoi(*userInput) > whoPlacedBet.getBalance());

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameTurnBetBuildSetAmmountBetted(std::stoi(*userInput))}
    );

    dbgLog_->buildDebugLogs();
    
    ammountBetted_ = std::stoi(*userInput);
    delete userInput;
}

/// @brief Sets up class attributes via askForBetAmmount, -Type and more specific 
/// information depending on bet type player choose
/// @param whoPlacedBet current Player 
void Bet::buildBet(const Player& whoPlacedBet)
{

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGaneTurnBetBetBuild}
    );

    dbgLog_->buildDebugLogs();

    askForBetAmmount(whoPlacedBet);
    askForBetType();

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameTurnBetGetDetails}
    );

    dbgLog_->buildDebugLogs();

    switch (betType_)
    {
    case BetType::StraightUp:
        askStraightUp();
        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnBetBuildBetStraightUpSet(whoPlacedBet.getNickName(), guessedNumber_)}
        );

        break;
    case BetType::DozenBet:
        askDozenBet();

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnBetBuildBetDozenSet(whoPlacedBet.getNickName(), std::to_string(static_cast<int>(betType_)))}
        );

        break;
    case BetType::EvenOdd:
        askEvenOdd();

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnBetBuildBetIsOddChoosenSet(whoPlacedBet.getNickName(), isOddChoosen_ )}
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

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnBetBuildGetInput}
        );

        do
        {
            std::getline(std::cin, *userInput);
            if(!ValidateInput::isStringNumber(*userInput))
            {
                std::cout << "You may only place postivie numeric values\n";

                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
                );
            }           

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
        );


        } while (!ValidateInput::isStringNumber(*userInput));
        
        if(std::stoi(*userInput) > MAX_POSSIBLE_LUCKY_NUMBER)
        {
            std::cout << "Your entry cannot be greater than " << MAX_POSSIBLE_LUCKY_NUMBER << std::endl;            
        }

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
        );

        dbgLog_->buildDebugLogs();
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

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnBetBuildGetInput}
        );

        do
        {
            std::getline(std::cin, *userInput);
            if(!ValidateInput::isStringNumber(*userInput))
            {
                std::cout << "Please enter a numeric value only\n";
                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
                );                
            }
        } while (!ValidateInput::isStringNumber(*userInput));
        if(std::stoi(*userInput) < 1 || std::stoi(*userInput) > 3)
        {
            std::cout << "Plase enter values within range 1 to 3\n";
            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, ValidateInput::isStringNumber(*userInput))}
            );                   
        }
    } while (std::stoi(*userInput) < 1 || std::stoi(*userInput) > 3);

    GuessedNumberRange_ = static_cast<GuessedNumberRangeType>(std::stoi(*userInput));

    delete userInput;
}

/// @brief Builds Odd/Even type of bet.
void Bet::askEvenOdd()
{

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameTurnBetBuildGetInput}
    );

    std::string* userInput = new std::string;
    std::cout << "Is lucky number odd or even?\n";
    do
    {
        std::getline(std::cin, *userInput);
        if(!Bet::isStringValid(*userInput))
        {
            std::cout << "It's either odd or even\n";

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameTurnBetBuildGetInputResult(*userInput, Bet::isStringValid(*userInput))}
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

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameTurnBetPlayerPassed(currentTurnPlayer_.getNickName())}
    );

    std::cout << currentTurnPlayer_.getNickName() << " - has passed this turn!\n";
}

/// @brief Passing constructor
/// @param currentTurnPlayer 
Bet::Bet(const Player& currentTurnPlayer, DebugLogger* dbLog)
{   
    dbgLog_ = dbLog;

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogClassBetInitialize}
    );

    dbLog->buildDebugLogs();

    currentTurnPlayer_ = currentTurnPlayer;
    betType_ = BetType::Pass;
    winningOdds_ = -1.0;
    ammountBetted_ = 0;
    Pass();
}