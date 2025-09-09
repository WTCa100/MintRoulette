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
    
    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameTurnBettingPhase}
    );

    dbgLog_->buildDebugLogs();

    for(int i = 0; i < currentPlayers_.size(); i++)
    {
        std::cout << "It's " << currentPlayers_[i]->getNickName() << "'s turn\n";
        if(!currentPlayers_[i]->getPlayerIsBot())
        {
            std::cout << "You have: " << currentPlayers_[i]->getBalance() << " worth of balance\n";
        }
        else
        {
            std::cout << "This bot have: " << currentPlayers_[i]->getBalance() << " worth of balance\n";
        }
        
        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnShowPlayer(currentPlayers_[i]->getNickName(), currentPlayers_[i]->getBalance(), currentPlayers_[i]->getPlayerIsBot()),
             dbgLog_->dbLogLoggerGetMessage(gameLog_->logGameTurnStartPlayerState(currentPlayers_[i]->getNickName(),
                                                                                 currentPlayers_[i]->getBalance()))}
        );
        
        dbgLog_->buildDebugLogs();

        gameLog_->addLog(
            gameLog_->logGameTurnStartPlayerState(currentPlayers_[i]->getNickName(),
                                                  currentPlayers_[i]->getBalance())
        );

        if(!currentPlayers_[i]->getPlayerIsBot())
        {
            // Check if player is willing to place bet
            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameTurnAskForBet(currentPlayers_[i]->getNickName())}
            );

            if(askForBet())
            {
                Bet* playerBet = new Bet(dbgLog_);
                playerBet->buildBet(*currentPlayers_[i]);
                playerAndBets_.insert(std::make_pair(currentPlayers_[i], playerBet));

                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerPlacedBet(currentPlayers_[i],
                                                                                    playerBet->getAmmountBetted()) + " "),
                     dbgLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerBetDetails(currentPlayers_[i],
                                                                                     playerBet)),
                     dbgLog_->dbLogGameTurnMapUserWithBetValues(currentPlayers_[i]->getNickName(), std::to_string(playerBet->getAmmountBetted())),
                     dbgLog_->dbLogPlayerSetBetCount(currentPlayers_[i]->getNickName(), currentPlayers_[i]->getBetCount() + 1)
                    }
                );

                currentPlayers_[i]->setBetCount(currentPlayers_[i]->getBetCount() + 1);


                dbgLog_->buildDebugLogs();

                gameLog_->addLog(
                    gameLog_->logGamePlayerPlacedBet(currentPlayers_[i],
                                                    playerBet->getAmmountBetted()) + " " +
                    gameLog_->logGamePlayerBetDetails(currentPlayers_[i],
                                                    playerBet)
                );
            }        
            else
            {
                Bet* playerPass = new Bet(*currentPlayers_[i], dbgLog_);
                playerAndBets_.insert(std::make_pair(currentPlayers_[i], playerPass));

                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogPlayerSetPassCount(currentPlayers_[i]->getNickName(), currentPlayers_[i]->getPassCount() + 1),
                     dbgLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerPassed(currentPlayers_[i]->getNickName()))}
                );

                currentPlayers_[i]->setPassCount(currentPlayers_[i]->getPassCount() + 1);


                gameLog_->addLog(
                    gameLog_->logGamePlayerPassed(currentPlayers_[i]->getNickName())
                );
            }
        }
        else
        {

            Ai* botBrain = new Ai(currentPlayers_[i], dbgLog_);

            std::cout << "Bot player " << currentPlayers_[i]->getNickName() << std::endl;

            if(botBrain->chooseActionBetOrPass())
            {

                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogGameTurnBetAiChooseActionWithBalanceResult(true, currentPlayers_[i]->getBalance())}
                );

                dbgLog_->buildDebugLogs();

                std::cout << "Decided to bet:";
                Bet* botBet = new Bet(dbgLog_);
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
                    botBet->getIsOddChoosen() ? std::cout << "thinking that the lucky number is odd\n" : std::cout << "thinking that the lucky number is even\n";
                    break;
                }

                std::cout << "Worth: " << botBet->getAmmountBetted() << std::endl;

                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerPlacedBet(currentPlayers_[i],
                                                   botBet->getAmmountBetted()) + " " +
                                                   gameLog_->logGamePlayerBetDetails(currentPlayers_[i],
                                                   botBet)),
                     dbgLog_->dbLogPlayerSetBetCount(currentPlayers_[i]->getNickName(), currentPlayers_[i]->getBetCount() + 1)}
                );
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
                Bet* playerPass = new Bet(*currentPlayers_[i], dbgLog_);
                playerAndBets_.insert(std::make_pair(currentPlayers_[i], playerPass));
                currentPlayers_[i]->setPassCount(currentPlayers_[i]->getPassCount() + 1);
                std::cout << "decided to pass this turn\n";

                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerPassed(currentPlayers_[i]->getNickName()))}
                );

                dbgLog_->buildDebugLogs();
                gameLog_->addLog(
                    gameLog_->logGamePlayerPassed(currentPlayers_[i]->getNickName())
                );
            }
            Sleep(100);

            delete botBrain;
        }

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogGameTurnPlayerEnd(currentPlayers_[i]->getNickName())}
            );

            dbgLog_->buildDebugLogs();

        }
}

void Turn::rollTheRoulette()
{

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameTurnRollTheRoulettePhase}
    );

    dbgLog_->buildDebugLogs();    

    std::vector<uint16_t> numbers(3, 37); // There will never be a situation where the number exceedes 36
    for(auto &i : numbers)
    {
        // bool isDuplicate = false;
        int generatedNumber;
        do
        {
            generatedNumber = randomizeNumber();
        } while (std::count(numbers.begin(), numbers.end(), generatedNumber) != 0);
        
        i = generatedNumber;
        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnRollTheGetRandomNumber(i)}
        );
    }
    size_t luckyNumPos = rand() % numbers.size();
    setLuckyNumber(numbers[luckyNumPos]);

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameTurnRollSetLuckyNumber(luckyNumber_),
         dbgLog_->dbLogLoggerGetMessage(gameLog_->logGameLuckyNumberGen(luckyNumber_))}
    );

    dbgLog_->buildDebugLogs();

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
    Sleep(1000);


    gameLog_->addLog(
        gameLog_->logGameLuckyNumberGen(luckyNumber_)
    );

    for(auto i : playerAndBets_)
    {
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
        }

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogGameTurnBetIsBetGood(i.first->getNickName(), i.second->getBetSucces())}
        );

        dbgLog_->buildDebugLogs();

    }

}

bool Turn::askForBet()
{

    dbgLog_->buildDebugLogs();

    std::string userInput;
    std::cout << "Are you betting (1) or passing (2)?\n";
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

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameTurnSummaryPhase,
         dbgLog_->dbLogLoggerGetMessage(gameLog_->logGameTurnSummaryBeginMessage())}
    );

    dbgLog_->buildDebugLogs();

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
            std::cout << " passed this turn!\n";
            break;
        }
        if(player.second->getBetType() != BetType::Pass)
        {
            double winAmmount = static_cast<double>(player.second->getAmmountBetted()) / 
                                static_cast<double>(player.second->getWinningOdds());
            int currentPlayerBalance = player.first->getBalance();
            if(player.second->getBetSucces())
            {

                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogGameTurnSumPlayerWonMoney(player.first->getNickName(), currentPlayerBalance, winAmmount)}
                );

                std::cout << "and got it!\n";
                std::cout << player.first->getNickName() <<" won " << static_cast<int>(winAmmount)  <<"!\n";
                player.first->setBalance(currentPlayerBalance + static_cast<int>(winAmmount));
                player.first->setMoneyAccumulated(player.first->getMoneyAccumulated() + static_cast<int>(winAmmount));
                player.first->setGoodBetCount(player.first->getGoodBetCount() + 1);

            }
            else
            {

                dbgLog_->addDebugLog(
                    {dbgLog_->dbLogGameTurnSumPlayerNotWonMoney(player.first->getNickName(), currentPlayerBalance, player.second->getAmmountBetted())}
                );

                std::cout << "and did not got it right!\n";
                std::cout << player.first->getNickName() <<" lost " << player.second->getAmmountBetted() <<"!\n";
                player.first->setBalance(currentPlayerBalance - player.second->getAmmountBetted());
                player.first->setMoneyLost(player.first->getMoneyLost() + player.second->getAmmountBetted());
            }

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerBetSummarize(player.first,
                                                                                   player.second,
                                                                                   winAmmount))}
            );

            dbgLog_->buildDebugLogs();

            gameLog_->addLog(
                gameLog_->logGamePlayerBetSummarize(player.first,
                                                    player.second,
                                                    winAmmount)
            );

        }


    }

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogLoggerGetMessage(gameLog_->logGameTurnSummaryEndMessage()),
         dbgLog_->dbLogGameTurnIdEnd(turnNumber_)}
    );

    dbgLog_->buildDebugLogs();

    gameLog_->addLog(
        gameLog_->logGameTurnSummaryEndMessage()
    );

    std::cout << "End of turn: " << turnNumber_ << "!\n";
    
}

void Turn::playTurn()
{
    dbgLog_->addDebugLog(
        {dbgLog_->dbLogGameTurnIdStarts(turnNumber_)}
        );
    dbgLog_->buildDebugLogs();

    std::cout << "Turn " << turnNumber_ << std::endl;
    bettingPhase();
    rollTheRoulette();
    summaryPhase();
}

Turn::~Turn()
{
    dbgLog_->addDebugLog(
        {dbgLog_->dbLogClassTurnDestruct}
    );

    dbgLog_->buildDebugLogs();

}