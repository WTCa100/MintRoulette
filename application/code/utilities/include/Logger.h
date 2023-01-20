#pragma once

#include <string>
#include <fstream>
#include <vector>

// Get headers
#include "./FileManager.h"
#include "../../game/include/Bet.h"
#include "../../game/include/Player.h"


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
    std::string logGameTurnStart(const uint16_t& turnId) const;
    std::string logGameTurnStartPlayerState(const std::string& playerName,
                                            const uint32_t& currentBankBalance) const;
    std::string logGamePlayerPlacedBet(const Player* whoPlacedBet,
                                       const uint32_t& betAmmount) const;
    std::string logGamePlayerBetDetails(const Player* whoPlacedBet,
                                        Bet* betPlaced) const;
    std::string logGamePlayerPassed(const std::string& playerName) const;                                       
    std::string logGameLuckyNumberGen(const uint16_t& luckyNumber) const;
    std::string logGamePlayerBetSummarize(const Player* targetPlayer,
                                          Bet* betPlaced,
                                          const double& winAmmount = 0) const;
    std::string logGameTurnEnd(const uint16_t& turnId) const;
    std::string logGamePlayerElimination(const std::string& playerEliminated) const;
    std::string logGamePlayerSummerizeGame(const Player* playerToSum) const;
    std::string logGameHasEnded() const;
    std::string logGameEndedEarly() const;

    Logger(FileManager* fManager) {fManager_ = fManager;};
    ~Logger();



    private:
    std::string logFileName_;
    FileManager* fManager_;
    std::ofstream logFile_;
    std::vector <std::string> logLines_;
};