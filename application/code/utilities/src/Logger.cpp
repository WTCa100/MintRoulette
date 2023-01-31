#include <iostream>
#include <ctime>

#include "../include/Logger.h"
#include "../include/Paths.h"
#include "../include/MaxValues.h"

void Logger::touchLog(const uint32_t& gameNumber)
{
    std::string logsPath = FILE_GAME_SAVE_LOG;
    std::string logFileExt = EXT_GAME_LOG;
    logFileName_ = "GameNr" + std::to_string(gameNumber) + logFileExt;
    fManager_->touch(FileType::GameSave, std::to_string(gameNumber));
    std::cout << "Debug: Logger: File: Creation of: " << logsPath + "/" + logFileName_ << std::endl;
    logFile_.open(logsPath + "/" + logFileName_,
                  std::ios::out);

    if(!logFile_.is_open())
    {
        std::cout << "Could not open file.\n Skipping\n";
    }
}

void Logger::addLog(const std::string& log)
{
    logLines_.push_back(logAddTimeStamp() + log);
}

Logger::~Logger()
{
    logFile_.close();
}

void Logger::buildLogs() 
{

    for(auto log : logLines_)
    {
        logFile_ << log << std::endl;
    }
    
    // Prevents from duplicated log entries
    logLines_.clear();
}

// Log Messages

std::string Logger::logAddTimeStamp()
{
  time_t rawTime;
  struct tm * timeInfo;
  char buffer[80];

  time (&rawTime);
  timeInfo = localtime(&rawTime);

  strftime(buffer,sizeof(buffer),"%d-%m-%Y:%H:%M:%S: ",timeInfo);
  std::string timeStamp(buffer);

    return timeStamp;
}

std::string Logger::logInitialGameConfig(const uint16_t& gameNum,
                                         const uint16_t& numOfPlayers,
                                         const uint32_t& initBankBalance) const
{
    return "Game nr " + std::to_string(gameNum) + " has started with: " + 
           std::to_string(numOfPlayers) + " players each starting with " + 
           std::to_string(initBankBalance) + " at their bank"; 
}

std::string Logger::logGamePlayerCreation(const std::string& playerName,
                                          const uint16_t& playerNumber) const
{
    return "Player " + std::to_string(playerNumber) + " with name " + playerName + " just appeared!";
}

std::string Logger::logGameTurnStart(const uint16_t& turnId) const
{
    return "Turn " + std::to_string(turnId) + " have started";
}

std::string Logger::logGameTurnStartPlayerState(const std::string& playerName,
                                                const uint32_t& currentBankBalance) const
{
    return "Player " + playerName + " has " + std::to_string(currentBankBalance) + " money on bank";
}

std::string Logger::logGamePlayerBetDetails(const Player* whoPlacedBet,
                                            Bet* betPlaced) const
{
    std::string logMsg = whoPlacedBet->getNickName();
    switch (betPlaced->getBetType())
    {
    case BetType::StraightUp:
        logMsg += " picked straight up with " + std::to_string(betPlaced->getGuessedNumber()) + " as lucky number!"; 
        break;
    case BetType::DozenBet:
        logMsg += " picked dozen bet with guessing that the lucky number is between ";
        switch (betPlaced->getGuessedNumberRange())
        {
        case GuessedNumberRangeType::LowerRange:
            logMsg += std::to_string(MIN_LOWER_RANGE) + " and " + std::to_string(MAX_LOWER_RANGE); 
            break;
        case GuessedNumberRangeType::MiddleRange:
            logMsg += std::to_string(MIN_MIDDLE_RANGE) + " and " + std::to_string(MAX_MIDDLE_RANGE); 
            break;
        case GuessedNumberRangeType::UpperRange:
            logMsg += std::to_string(MIN_UPPER_RANGE) + " and " + std::to_string(MAX_UPPER_RANGE); 
            break;
        }
        break;
    case BetType::EvenOdd:
        logMsg += " picked even/odd bet and guessed that the lucky number is ";
        if(betPlaced->getIsOddChoosen())
        {
            logMsg += "odd";
        }
        else
        {
            logMsg += "even";
        }
        break;
    default:
        break;
    }

    return logMsg;
}


std::string Logger::logGamePlayerPlacedBet(const Player* whoPlacedBet,
                                           const uint32_t& betAmmount)  const
{
    std::string logMsg = whoPlacedBet->getNickName();

    // Check for all in
    if(betAmmount == whoPlacedBet->getBalance())
    {
        logMsg += " went all in!";
    }
    else
    {
        logMsg += " placed bet worth " + std::to_string(betAmmount);
    }

    return logMsg;
}

std::string Logger::logGamePlayerPassed(const std::string& playerName) const
{
    return playerName + " passed this turn.";
}

std::string Logger::logGameLuckyNumberGen(const uint16_t& luckyNumber) const
{
    return "Roulette have rolled " + std::to_string(luckyNumber) + " as the lucky number!";
}

std::string Logger::logGamePlayerBetSummarize(const Player* targetPlayer,
                                              Bet* betPlaced,
                                              const double& winAmmount) const
{
    std::string logMsg = targetPlayer->getNickName();
    if(betPlaced->getBetSucces())
    {
        logMsg += " was lucky this time and won " + std::to_string(static_cast<uint32_t>(winAmmount));
    }
    else
    {
        logMsg += " was not lucky this time and lost " + std::to_string(betPlaced->getAmmountBetted());
    }
    logMsg += " ammount of money";

    return logMsg;
}

std::string Logger::logGameTurnEnd(const uint16_t& turnId) const
{
    return "Turn " + std::to_string(turnId) + " has ended";    
}

std::string Logger::logGameTurnSummaryBeginMessage() const
{
    return "Begining of turn summary";
}

std::string Logger::logGameTurnSummaryEndMessage() const
{
    return "End of turn summary";
}

std::string Logger::logGamePlayerElimination(const std::string& playerEliminated) const
{
    return playerEliminated + " got eliminated!";
}

std::string Logger::logGamePlayerSummerizeGame(const Player* playerToSum) const
{
    std::string logMsg = playerToSum->getNickName() + " ended the game with " + std::to_string(playerToSum->getBalance());

    if(playerToSum->getBetCount())
    {
        logMsg += ". Managed to place " + std::to_string(playerToSum->getBetCount()) + " bets";
    }
    else
    {
        logMsg += ". Placed no bets!";
    }

    if(playerToSum->getPassCount())
    {
        logMsg += ". Passed " + std::to_string(playerToSum->getPassCount());
        if(playerToSum->getPassCount() == 1)
        {
            logMsg += " turn";
        }
        else
        {
            logMsg += " turns";
        }
    }
    else
    {
        logMsg += ". Passed no turn!";
    }

    if(playerToSum->getMoneyAccumulated() == 0 && playerToSum->getMoneyLost() == 0)
    {
        logMsg += ". Neither lost nor won any money";
    }
    else 
    {
        if(playerToSum->getMoneyAccumulated() > 0)
        {
            logMsg += ". Managed to obtain " + std::to_string(playerToSum->getMoneyAccumulated()) + " additional ammount of money";
        }
        else
        {
            logMsg += ". Did not won any money!";
        }

        if(playerToSum->getMoneyLost() > 0)
        {
            logMsg += ". Lost " +  std::to_string(playerToSum->getMoneyLost()) + " worth of money";        
        }
        else
        {
            logMsg == ". Did not lost any money!";
        }
    }

    return logMsg;
}

std::string Logger::logGameHasEnded() const
{
    return "Game has ended here!";
}

std::string Logger::logGameEndedEarly() const
{
    return "Game ended early!";
}