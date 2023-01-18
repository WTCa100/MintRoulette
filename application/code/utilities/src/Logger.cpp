#include <iostream>

#include "../include/Logger.h"
#include "../include/Paths.h"

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
    logLines_.push_back(log);
}

Logger::~Logger()
{
    logFile_.close();
}

void Logger::buildLogs() 
{

    for(auto log : logLines_)
    {
        std::cout << "Debug: Logger: Log: Write: " << log << std::endl;
        logFile_ << log << std::endl;
    }
    
    // Prevents from duplicated log entries
    logLines_.clear();
}

// Log Messages

std::string Logger::logInitialGameConfig(const uint16_t& gameNum,
                                         const uint16_t& numOfPlayers,
                                         const uint32_t& initBankBalance) const
{
    return "Game nr " + std::to_string(gameNum) + " has started with: " + 
           std::to_string(numOfPlayers) + " player each starting with " + 
           std::to_string(initBankBalance); 
}

std::string Logger::logGamePlayerCreation(const std::string& playerName,
                                          const uint16_t& playerNumber) const
{
    return "Player " + std::to_string(playerNumber) + " with name " + playerName + " just appeared!";
}