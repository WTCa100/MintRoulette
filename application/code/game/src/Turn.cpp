#include <iostream>
#include <windows.h>

// Get header
#include "../include/Turn.h"
#include "../include/Bet.h"
#include "../include/Ai.h"
#include "../../utilities/include/MaxValues.h"

// Get source
#include "./Bet.cpp"
#include "../../utilities/src/Logger.cpp"
#include "./Ai.cpp"

/// @brief Get random number from specified range
/// @return Random number from range 0 to 36 as uint_16
uint16_t Turn::randomizeNumber()
{
    return static_cast<uint16_t>(rand()% 37);
}

/// @brief Iterate through every player, display nick and balance and promp them if they want to place a bet.
/// @note depending on whether or not player wants to bet a different Bet initializer is created.
void Turn::bettingPhase()
{
    for(int i = 0; i < currentPlayers_.size(); i++)
    {
        std::cout << "Debug info: " << currentPlayers_[i]->getNickName() << " turn has started\n";
        std::cout << "It's " << currentPlayers_[i]->getNickName() << "'s turn\n";
        if(!currentPlayers_[i]->getPlayerIsBot())
        {
            std::cout << "You have: " << currentPlayers_[i]->getBalance() << " worth of balance\n";
        }
        else
        {
            std::cout << "This bot have: " << currentPlayers_[i]->getBalance() << " worth of balance\n";
        }
        gameLog_->addLog(
            gameLog_->logGameTurnStartPlayerState(currentPlayers_[i]->getNickName(),
                                                  currentPlayers_[i]->getBalance())
        );
        if(!currentPlayers_[i]->getPlayerIsBot())
        {
            // Aske player if he wants to bet
            if(askForBet())
            {
                Bet* playerBet = new Bet();
                playerBet->buildBet(*currentPlayers_[i]);
                playerAndBets_.insert(std::make_pair(currentPlayers_[i], playerBet));
                currentPlayers_[i]->setBetCount(currentPlayers_[i]->getBetCount() + 1);

                gameLog_->addLog(
                    gameLog_->logGamePlayerPlacedBet(currentPlayers_[i],
                                                    playerBet->getAmmountBetted()) + " " +
                    gameLog_->logGamePlayerBetDetails(currentPlayers_[i],
                                                    playerBet)
                );
            }        
            else
            {
                Bet* playerPass = new Bet(*currentPlayers_[i]);
                playerAndBets_.insert(std::make_pair(currentPlayers_[i], playerPass));
                currentPlayers_[i]->setPassCount(currentPlayers_[i]->getPassCount() + 1);

                gameLog_->addLog(
                    gameLog_->logGamePlayerPassed(currentPlayers_[i]->getNickName())
                );
            }
            std::cout << "Debug Info: playerAndBets: size: " << playerAndBets_.size() << std::endl;
            std::cout << "Debug info: " << currentPlayers_[i]->getNickName() << " turn has ended\n";
        }
        else
        {

            Ai* botBrain = new Ai(currentPlayers_[i]);

            std::cout << "Bot player " << currentPlayers_[i]->getNickName();

            if(botBrain->chooseActionBetOrPass())
            {
                std::cout << " decided to bet:";
                Bet* botBet = new Bet();
                botBet = botBrain->buildBet(botBet);
                switch (botBet->getBetType())
                {
                case BetType::StraightUp:
                    std::cout << " straight up with " << botBet->getGuessedNumber() << " as lucky number\n";
                    break;
                case BetType::DozenBet:
                    std::cout << " dozen with ";
                    switch (botBet->getGuessedNumberRange())
                    {
                    case GuessedNumberRangeType::UpperRange:
                        std::cout << MIN_UPPER_RANGE << " and " << MAX_UPPER_RANGE << " as lucky number range\n";
                        break;
                    case GuessedNumberRangeType::MiddleRange:
                        std::cout << MIN_MIDDLE_RANGE << " and " << MAX_MIDDLE_RANGE << " as lucky number range\n";
                        break;
                    case GuessedNumberRangeType::LowerRange:
                        std::cout << MIN_LOWER_RANGE << " and " << MAX_LOWER_RANGE << " as lucky number range\n";
                        break;
                    }
                    break;
                case BetType::EvenOdd:
                    std::cout << " even/odd ";
                    botBet->getIsOddChoosen() ? std::cout << " thinking that the lucky number is odd\n" : std::cout << " thinking that the lucky number is even\n";
                    break;
                }

                std::cout << " worth " << botBet->getAmmountBetted() << std::endl;

                playerAndBets_.insert(std::make_pair(currentPlayers_[i], botBet));
                currentPlayers_[i]->setBetCount(currentPlayers_[i]->getBetCount() + 1);

                gameLog_->addLog(
                    gameLog_->logGamePlayerPlacedBet(currentPlayers_[i],
                                                    botBet->getAmmountBetted()) + " " +
                    gameLog_->logGamePlayerBetDetails(currentPlayers_[i],
                                                    botBet)
                );               

            }
            else
            {
                Bet* playerPass = new Bet(*currentPlayers_[i]);
                playerAndBets_.insert(std::make_pair(currentPlayers_[i], playerPass));
                currentPlayers_[i]->setPassCount(currentPlayers_[i]->getPassCount() + 1);
                std::cout << " decided to pass this turn\n";

                gameLog_->addLog(
                    gameLog_->logGamePlayerPassed(currentPlayers_[i]->getNickName())
                );
            }
            Sleep(100);

            delete botBrain;
        }

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

    gameLog_->addLog(
        gameLog_->logGameLuckyNumberGen(luckyNumber_)
    );

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
                case GuessedNumberRangeType::LowerRange:
                i.second->setBetSucces(luckyNumber_ >= MIN_LOWER_RANGE && luckyNumber_ <= MAX_LOWER_RANGE);
                break;
                case GuessedNumberRangeType::MiddleRange:
                i.second->setBetSucces(luckyNumber_ >= MIN_MIDDLE_RANGE && luckyNumber_ <= MAX_MIDDLE_RANGE);
                break;
                case GuessedNumberRangeType::UpperRange:
                i.second->setBetSucces(luckyNumber_ >= MIN_UPPER_RANGE && luckyNumber_ <= MAX_UPPER_RANGE);
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

    for(auto debugPlayer : playerAndBets_)
    {
        std::cout << "Debug Info: Player: NickName: " << debugPlayer.first->getNickName() << std::endl;
        std::cout << "Debug Info: Bet: Value: " << debugPlayer.second->getAmmountBetted() << std::endl;
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
    std::cout << "Summary!\n"; 

    gameLog_->addLog(
        gameLog_->logGameTurnSummaryBeginMessage()
    );

    for(auto& player : playerAndBets_)
    {
        std::cout << player.first->getNickName() << " ";
        switch (player.second->getBetType())
        {
        case BetType::StraightUp:
            std::cout << "betted straight up with " 
                      << player.second->getGuessedNumber();
            break;
        case BetType::DozenBet:
            std::cout << "betted dozen on number between ";
            switch (player.second->getGuessedNumberRange())
            {
            case GuessedNumberRangeType::LowerRange:
                std::cout << MIN_LOWER_RANGE << " and " 
                          << MAX_LOWER_RANGE  << std::endl;
                break;
            case GuessedNumberRangeType::MiddleRange:
                std::cout << MIN_MIDDLE_RANGE << " and "
                          << MAX_MIDDLE_RANGE << std::endl;
                break;
            case GuessedNumberRangeType::UpperRange:
                std::cout << MIN_UPPER_RANGE << " and "
                          << MAX_UPPER_RANGE << std::endl;
            }
            break;
        case BetType::EvenOdd:
            if(player.second->getIsOddChoosen())
            {
                std::cout << "betted for odd ";
            }
            else
            {
                std::cout << "betted for even ";
            }
            break;
        default:
            std::cout << "passed this turn!\n";
            break;
        }
        if(player.second->getBetType() != BetType::Pass)
        {
            double winAmmount = static_cast<double>(player.second->getAmmountBetted()) / 
                                static_cast<double>(player.second->getWinningOdds());
            int currentPlayerBalance = player.first->getBalance();
            if(player.second->getBetSucces())
            {
                std::cout << "and got it!\n";
                std::cout << player.first->getNickName() <<" won " << static_cast<int>(winAmmount)  <<"!\n";
                player.first->setBalance(currentPlayerBalance + static_cast<int>(winAmmount));
                player.first->setMoneyAccumulated(player.first->getMoneyAccumulated() + static_cast<int>(winAmmount));
                player.first->setGoodBetCount(player.first->getGoodBetCount() + 1);

            }
            else
            {
                std::cout << "and did not got it right!\n";
                std::cout << player.first->getNickName() <<" lost " << player.second->getAmmountBetted() <<"!\n";
                player.first->setBalance(currentPlayerBalance - player.second->getAmmountBetted());
                player.first->setMoneyLost(player.first->getMoneyLost() + player.second->getAmmountBetted());
            }

            gameLog_->addLog(
                gameLog_->logGamePlayerBetSummarize(player.first,
                                                    player.second,
                                                    winAmmount)
            );

        }


    }

    gameLog_->addLog(
        gameLog_->logGameTurnSummaryEndMessage()
    );

    std::cout << "End of turn: " << turnNumber_ << "!\n";
    
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
    std::cout << "Debug Info: Turn: " << turnNumber_ << " Teardown\n";
}