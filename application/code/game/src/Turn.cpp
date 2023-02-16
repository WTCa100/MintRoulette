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
    
    dbLog_->addDebugLog(
        {dbLog_->dbLogGameTurnBettingPhase}
    );

    dbLog_->buildDebugLogs();

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
        
        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnShowPlayer(currentPlayers_[i]->getNickName(), currentPlayers_[i]->getBalance(), currentPlayers_[i]->getPlayerIsBot()),
             dbLog_->dbLogLoggerGetMessage(gameLog_->logGameTurnStartPlayerState(currentPlayers_[i]->getNickName(),
                                                                                 currentPlayers_[i]->getBalance()))}
        );
        
        dbLog_->buildDebugLogs();

        gameLog_->addLog(
            gameLog_->logGameTurnStartPlayerState(currentPlayers_[i]->getNickName(),
                                                  currentPlayers_[i]->getBalance())
        );

        if(!currentPlayers_[i]->getPlayerIsBot())
        {
            // Check if player is willing to place bet
            dbLog_->addDebugLog(
                {dbLog_->dbLogGameTurnAskForBet(currentPlayers_[i]->getNickName())}
            );

            if(askForBet())
            {
                Bet* playerBet = new Bet(dbLog_);
                playerBet->buildBet(*currentPlayers_[i]);
                playerAndBets_.insert(std::make_pair(currentPlayers_[i], playerBet));

                dbLog_->addDebugLog(
                    {dbLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerPlacedBet(currentPlayers_[i],
                                                                                    playerBet->getAmmountBetted()) + " "),
                     dbLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerBetDetails(currentPlayers_[i],
                                                                                     playerBet)),
                     dbLog_->dbLogGameTurnMapUserWithBetValues(currentPlayers_[i]->getNickName(), std::to_string(playerBet->getAmmountBetted())),
                     dbLog_->dbLogPlayerSetBetCount(currentPlayers_[i]->getNickName(), currentPlayers_[i]->getBetCount() + 1)
                    }
                );

                currentPlayers_[i]->setBetCount(currentPlayers_[i]->getBetCount() + 1);


                dbLog_->buildDebugLogs();

                gameLog_->addLog(
                    gameLog_->logGamePlayerPlacedBet(currentPlayers_[i],
                                                    playerBet->getAmmountBetted()) + " " +
                    gameLog_->logGamePlayerBetDetails(currentPlayers_[i],
                                                    playerBet)
                );
            }        
            else
            {
                Bet* playerPass = new Bet(*currentPlayers_[i], dbLog_);
                playerAndBets_.insert(std::make_pair(currentPlayers_[i], playerPass));

                dbLog_->addDebugLog(
                    {dbLog_->dbLogPlayerSetPassCount(currentPlayers_[i]->getNickName(), currentPlayers_[i]->getPassCount() + 1),
                     dbLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerPassed(currentPlayers_[i]->getNickName()))}
                );

                currentPlayers_[i]->setPassCount(currentPlayers_[i]->getPassCount() + 1);


                gameLog_->addLog(
                    gameLog_->logGamePlayerPassed(currentPlayers_[i]->getNickName())
                );
            }
        }
        else
        {

            Ai* botBrain = new Ai(currentPlayers_[i], dbLog_);

            std::cout << "Bot player " << currentPlayers_[i]->getNickName();

            if(botBrain->chooseActionBetOrPass())
            {

                dbLog_->addDebugLog(
                    {dbLog_->dbLogGameTurnBetAiChooseActionWithBalanceResult(true, currentPlayers_[i]->getBalance())}
                );

                dbLog_->buildDebugLogs();

                std::cout << " decided to bet:";
                Bet* botBet = new Bet(dbLog_);
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

                dbLog_->addDebugLog(
                    {dbLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerPlacedBet(currentPlayers_[i],
                                                   botBet->getAmmountBetted()) + " " +
                                                   gameLog_->logGamePlayerBetDetails(currentPlayers_[i],
                                                   botBet)),
                     dbLog_->dbLogPlayerSetBetCount(currentPlayers_[i]->getNickName(), currentPlayers_[i]->getBetCount() + 1)}
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
                Bet* playerPass = new Bet(*currentPlayers_[i], dbLog_);
                playerAndBets_.insert(std::make_pair(currentPlayers_[i], playerPass));
                currentPlayers_[i]->setPassCount(currentPlayers_[i]->getPassCount() + 1);
                std::cout << " decided to pass this turn\n";

                dbLog_->addDebugLog(
                    {dbLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerPassed(currentPlayers_[i]->getNickName()))}
                );

                dbLog_->buildDebugLogs();
                gameLog_->addLog(
                    gameLog_->logGamePlayerPassed(currentPlayers_[i]->getNickName())
                );
            }
            Sleep(100);

            delete botBrain;
        }

            dbLog_->addDebugLog(
                {dbLog_->dbLogGameTurnPlayerEnd(currentPlayers_[i]->getNickName())}
            );

            dbLog_->buildDebugLogs();

        }
}

void Turn::rollTheRoulette()
{

    dbLog_->addDebugLog(
        {dbLog_->dbLogGameTurnRollTheRoulettePhase}
    );

    dbLog_->buildDebugLogs();    

    std::vector<uint16_t> numbers(3, 0);
    for(auto &i : numbers)
    {
        i = randomizeNumber();
        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnRollTheGetRandomNumber(i)}
        );
    }
    size_t luckyNumPos = rand() % numbers.size();
    setLuckyNumber(numbers[luckyNumPos]);

    dbLog_->addDebugLog(
        {dbLog_->dbLogGameTurnRollSetLuckyNumber(luckyNumber_),
         dbLog_->dbLogLoggerGetMessage(gameLog_->logGameLuckyNumberGen(luckyNumber_))}
    );

    dbLog_->buildDebugLogs();

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

        dbLog_->addDebugLog(
            {dbLog_->dbLogGameTurnBetIsBetGood(i.first->getNickName(), i.second->getBetSucces())}
        );

        dbLog_->buildDebugLogs();

    }

    for(auto debugPlayer : playerAndBets_)
    {
        std::cout << "Debug Info: Player: NickName: " << debugPlayer.first->getNickName() << std::endl;
        std::cout << "Debug Info: Bet: Value: " << debugPlayer.second->getAmmountBetted() << std::endl;
    }
}

bool Turn::askForBet()
{

    dbLog_->buildDebugLogs();

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

    dbLog_->addDebugLog(
        {dbLog_->dbLogGameTurnSummaryPhase,
         dbLog_->dbLogLoggerGetMessage(gameLog_->logGameTurnSummaryBeginMessage())}
    );

    dbLog_->buildDebugLogs();

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

                dbLog_->addDebugLog(
                    {dbLog_->dbLogGameTurnSumPlayerWonMoney(player.first->getNickName(), currentPlayerBalance, winAmmount)}
                );

                std::cout << "and got it!\n";
                std::cout << player.first->getNickName() <<" won " << static_cast<int>(winAmmount)  <<"!\n";
                player.first->setBalance(currentPlayerBalance + static_cast<int>(winAmmount));
                player.first->setMoneyAccumulated(player.first->getMoneyAccumulated() + static_cast<int>(winAmmount));
                player.first->setGoodBetCount(player.first->getGoodBetCount() + 1);

            }
            else
            {

                dbLog_->addDebugLog(
                    {dbLog_->dbLogGameTurnSumPlayerNotWonMoney(player.first->getNickName(), currentPlayerBalance, player.second->getAmmountBetted())}
                );

                std::cout << "and did not got it right!\n";
                std::cout << player.first->getNickName() <<" lost " << player.second->getAmmountBetted() <<"!\n";
                player.first->setBalance(currentPlayerBalance - player.second->getAmmountBetted());
                player.first->setMoneyLost(player.first->getMoneyLost() + player.second->getAmmountBetted());
            }

            dbLog_->addDebugLog(
                {dbLog_->dbLogLoggerGetMessage(gameLog_->logGamePlayerBetSummarize(player.first,
                                                                                   player.second,
                                                                                   winAmmount))}
            );

            dbLog_->buildDebugLogs();

            gameLog_->addLog(
                gameLog_->logGamePlayerBetSummarize(player.first,
                                                    player.second,
                                                    winAmmount)
            );

        }


    }

    dbLog_->addDebugLog(
        {dbLog_->dbLogLoggerGetMessage(gameLog_->logGameTurnSummaryEndMessage()),
         dbLog_->dbLogGameTurnIdEnd(turnNumber_)}
    );

    dbLog_->buildDebugLogs();

    gameLog_->addLog(
        gameLog_->logGameTurnSummaryEndMessage()
    );

    std::cout << "End of turn: " << turnNumber_ << "!\n";
    
}

void Turn::playTurn()
{
    dbLog_->addDebugLog(
        {dbLog_->dbLogGameTurnIdStarts(turnNumber_)}
        );
    dbLog_->buildDebugLogs();

    std::cout << "Turn " << turnNumber_ << std::endl;
    bettingPhase();
    rollTheRoulette();
    summaryPhase();
}

Turn::~Turn()
{
    dbLog_->addDebugLog(
        {dbLog_->dbLogClassTurnDestruct}
    );

    dbLog_->buildDebugLogs();

    std::cout << "Debug Info: Turn: " << turnNumber_ << " Teardown\n";
}