#pragma once

#include <string>
#include <fstream>
#include <vector>

// Get headers
#include "./FileManager.h"
#include "../../game/include/Player.h"
#include "../../game/include/Turn.h"


class Logger
{
    public:
    // Operating on log file and log content
    // Create log file
    void touchLog(const uint32_t& gameNumber);
    // Add log message to all logs stored
    void addLog(const std::string& log);
    // Prints logs into file
    void buildLogs();

    // Log messages
    std::string logInitialGameConfig(const uint16_t& gameNum,
                                     const uint16_t& numOfPlayers,
                                     const uint32_t& initBankBalance) const;
    std::string logGamePlayerCreation(const std::string& playerName,
                                      const uint16_t& playerNumber) const;

    Logger(FileManager* fManager) {fManager_ = fManager;};
    ~Logger();



    private:
    std::string logFileName_;
    FileManager* fManager_;
    std::ofstream logFile_;
    std::vector <std::string> logLines_;
};