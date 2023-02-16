#include "../include/DebugLogger.h"
#include "../include/Paths.h"

DebugLogger::DebugLogger()
{
    fileName_ = dbLogAddTimeStamp();
    std::cout << FILE_GAME_DEBUG_LOG_DBG_PATH << "/" + fileName_ << std::endl;
    logMessages_.clear();
    
}

std::string DebugLogger::dbLogAddTimeStamp()
{
  time_t rawTime;
  struct tm * timeInfo;
  char buffer[80];

  time (&rawTime);
  timeInfo = localtime(&rawTime);

  strftime(buffer,sizeof(buffer),"%d-%m-%Y-%H-%M-%S",timeInfo);
  std::string timeStamp(buffer);

    return timeStamp;
}

void DebugLogger::touchDbLog()
{
    std::string filePath = FILE_GAME_DEBUG_LOG_DBG_PATH;
    debugFile_.open(filePath + "/" + fileName_ + EXT_PROGRAM_LOG_DEBUG, std::ios::app);
    addDebugLog({"Debug: Application: File: Create: " + filePath + "/" + fileName_ + ".debug"});
    buildDebugLogs();
}

void DebugLogger::addDebugLog(std::vector<std::string> logMessages)
{
    for(auto& msg : logMessages)
    {
        logMessages_.push_back(dbLogAddTimeStamp() + ": " + msg);
    }
}

void DebugLogger::buildDebugLogs()
{
    for(auto& msg : logMessages_)
    {
        debugFile_ << msg << std::endl;
    }
    
    logMessages_.clear();

    // Write logs down
    debugFile_.close();
    std::string filePath = FILE_GAME_DEBUG_LOG_DBG_PATH;
    debugFile_.open(filePath + "/" + fileName_ + EXT_PROGRAM_LOG_DEBUG, std::ios::app);
}

// Log messages

// Universals/heplers

const std::string DebugLogger::helperDbLogBoolResult(const std::string& msgPath, const bool& checkResult)
{
    if(checkResult)
    {
        return msgPath + "Check: Result: True";
    }
    else
    {
        return msgPath + "Check: Result: False";
    }
}

const std::string DebugLogger::helperDbLogLoopStringVector(const std::string& msgPath, const std::vector<std::string>& interateThrough)
{
    std::string dbLogMsg = msgPath + "List: ";
    for(auto pos : interateThrough)
    {
        dbLogMsg += pos + "\n";
    }

    return dbLogMsg;
}

const std::string DebugLogger::helperDbLogVectorEmpty(const std::string& msgPath, const std::vector<std::string>& checkVector)
{
    return helperDbLogBoolResult(msgPath, checkVector.empty());
}

const std::string DebugLogger::helperDbLogAddContentToFile(const std::string& msgPath, const std::string& path, const std::string& fileName, const std::string& content)
{
    return msgPath + " Add: " + fileName + " At: " + path + " Content: " + content;
}

const std::string DebugLogger::helperDbLogCheckUserInput(const std::string& msgPath, const std::string& userInput, const bool& result)
{
    return helperDbLogBoolResult(msgPath + " Check: Input: " + userInput + " ", result);
}

// App Builder substance logs

 const std::string DebugLogger::dbLogAppBuilderFolderCheckList(std::set<std::string> foldersToCheck)
 {
    std::string dbLogMsg = helperDbLogPositionAppBuilderFolder + "RequiredCheck: List:\n";
    for(auto pos : foldersToCheck)
    {
        dbLogMsg += pos + "\n";
    }

    return dbLogMsg;
 }

const std::string DebugLogger::dbLogAppBuilderCheckFolder(const std::string& folder)
{
    return helperDbLogPositionAppBuilderFolder + "Check: " + folder;
}

const std::string DebugLogger::dbLogAppBuilderCheckFolderResult(const bool& checkResult)
{
    return helperDbLogBoolResult(helperDbLogPositionAppBuilderFolder, checkResult);
}


const std::string DebugLogger::dbLogAppBuilderCreateFolder(const std::string& folder)
{
    return helperDbLogPositionAppBuilderFolder + "Create: " + folder;
}

const std::string DebugLogger::dbLogAppBuilderIsInitLaunch(const bool& checkResult)
{
    return helperDbLogBoolResult(helperDbLogPositionAppBuilderFolder + "IsInitLaunch: ", checkResult);
}

const std::string DebugLogger::dbLogAppBuilderInitConfigPotentialGameListEmpty(const std::vector<std::string> checkVector)
{
    return helperDbLogVectorEmpty(helperDbLogPositionAppBuilderSetup + "PotentialGameList: IsEmpty: ", checkVector);
}

const std::string DebugLogger::dbLogAppBuilderInitConfigPotentialGameListShow(const std::vector<std::string>& gameList)
{
    return helperDbLogLoopStringVector(helperDbLogPositionAppBuilderSetup + "GameList: Show: ", gameList);
}

const std::string DebugLogger::dbLogAppBuilderInitConfigNextGameIdSet(const int& nextGameId)
{
    return helperDbLogPositionAppBuilderSetup + "NextGameId: Set: " + std::to_string(nextGameId);
}

const std::string DebugLogger::dbLogAppBuilderInitConfigGameVersion(const std::string& gameVersion)
{
    return helperDbLogPositionAppBuilderSetup + " AssignGameVersion: " + gameVersion;
}

const std::string DebugLogger::dbLogAppBuilderInitConfigAddContent(const std::string& path, const std::string& fileName, const std::string& content)
{
    return helperDbLogAddContentToFile(dbLogAppBuilderInitConfigBuild, path, fileName, content);
}

// File Manager substance logs

// File check/create/touch

const std::string DebugLogger::dbLogFmanagerCheckForFile(const std::string& path, const std::string& fileName)
{
    return helperDbLogPositionFManagerFiles + "Check: " + fileName +" Exists: At: " + path; 
}

const std::string DebugLogger::dbLogFManagerCheckForFileResult(const std::string& path, const std::string& filename, const bool& checkResult)
{
    return helperDbLogBoolResult(helperDbLogPositionFManagerFiles + path + "/" + filename + " ", checkResult);
}

const std::string DebugLogger::dbLogFManagerCreateFile(const std::string& path, const std::string& filename)
{
    return helperDbLogPositionFManagerFiles + "Create: " + filename + " At: " + path;
}

const std::string DebugLogger::dbLogFManagerTouchFile(const std::string& type, const std::string& path, const std::string& filename)
{
    return helperDbLogPositionFManagerFiles + "Touch: " + filename + " At: " + path + " As: " + type;
}

const std::string DebugLogger::dbLogFManagerFileAddContent(const std::string& path, const std::string& fileName, const std::string& content)
{
    return helperDbLogAddContentToFile(helperDbLogPositionFManagerFiles, path, fileName, content);
}

// Loading files from path
const std::string DebugLogger::dbLogFManagerLoadFilesFromPath(const std::string& path)
{
    return helperDbLogPositionFManagerLoadFilesFromPath + path;
}

const std::string DebugLogger::dbLogFManagerLoadFilesContent(const std::string& path, const std::string& filename, const std::vector<std::string> contents)
{
    return helperDbLogLoopStringVector(helperDbLogPositionFManagerFiles + filename + " At: " + path + " Content:", contents);
}

const std::string DebugLogger::dbLogFManagerLoadFilesContentEmpty(const std::string& path, const std::string& filename, const std::vector<std::string> checkVector)
{
    return helperDbLogVectorEmpty(helperDbLogPositionFManagerLoadFilesFromPath + "Path: " + path + " Contents: IsEmpty: ", checkVector);
}
const std::string DebugLogger::dbLogFManagerLoadFilesFromPathResult(const std::string& path, const std::vector<std::string>& filesList)
{
    std::string dbLogMsg = dbLogFManagerLoadFilesFromPath(path) + " ReturnedList: \n";
    for(auto pos : filesList)
    {
        dbLogMsg += pos + "\n";
    }

    return dbLogMsg;
}

// Operations on Init.cfg
const std::string DebugLogger::dbLogFManagerInitConfigEditTag(const std::string& tag, const std::string& newValue)
{
    return helperDbLogPositionFManagerInitConfig + "Add: Value: " + newValue + " ToTag: " + tag;
}

// Menu

const std::string DebugLogger::dbLogMenuCheckUserInput(const std::string& userInput, const bool& isGood)
{
    return helperDbLogCheckUserInput(helperDbLogPositionMenu, userInput, isGood);
}

// Game

const std::string DebugLogger::dbLogMenuMainGameListDisplay(const std::vector<std::string>& games)
{
    return helperDbLogLoopStringVector(dbLogMenuMainGameListChooseDetails, games);
}

// Player

const std::string DebugLogger::dbLogPlayerInitializedValues(const std::string& nickName, const int& globalMoneyAccumulated,
                                                            const int& globalMoneyLost, const int& globalGoodBetCount,
                                                            const int& globalBetCount, const int& globalPassCount,
                                                            const int& balance,  const double& globalGoodBetRatio, 
                                                            const int& playerOrder, const bool& isBot)
{
    std::string dbLogMsg = helperDbLogPositionGamePlayer + "Initialized: WithValues: \n";
    if(!nickName.empty())
    {
        dbLogMsg += "PlayerName: " + nickName + "\n";
    }
    if(globalMoneyAccumulated)
    {
        dbLogMsg += "GlobalMoneyAccumulated: " + std::to_string(globalMoneyAccumulated) + "\n";
    }
    if(globalMoneyLost)
    {
        dbLogMsg += "GlobalMoneyLost: " + std::to_string(globalMoneyLost) + "\n";
    }
    if(globalGoodBetCount)
    {
        dbLogMsg += "GlobalGoodBetCount: " + std::to_string(globalGoodBetCount) + "\n";
    }
    if(globalBetCount)
    {
        dbLogMsg += "GlobalBetCount: " + std::to_string(globalBetCount) + "\n";
    }
    if(globalPassCount)
    {
        dbLogMsg += "GlobalPassCount: " + std::to_string(globalPassCount) + "\n";
    }
    if(balance)
    {
        dbLogMsg += "Balance: " + std::to_string(balance) + "\n"; 
    }
    if(globalGoodBetRatio)
    {
        dbLogMsg += "GlobalGoodBetRatio: " + std::to_string(globalGoodBetRatio) + "\n";
    }
    if(playerOrder)
    {
        dbLogMsg += "PlayerOrder(ID): " + std::to_string(playerOrder) + "\n";
    }

    dbLogMsg += "IsBot: " + std::to_string(isBot);

    return dbLogMsg;
}

const std::string DebugLogger::dbLogGamePlayerMoveToGlobal(const std::string& nickName, std::vector<int> globalStatsEarly, std::vector<int> newGlobalStats, const double& oldRatio)
{
    std::string dbLogMsg = helperDbLogPositionGameSpecifiedPlayer(nickName) + "Moving values to global scope\n";

    double newRatio = 0;

    // Value of bet count
    if(globalStatsEarly[1] != 0)
    {
        newRatio = static_cast<double>(globalStatsEarly[2]) / static_cast<double>(globalStatsEarly[1]);
    }

    for(int i = 0; i < globalStatsEarly.size(); i++)
    {
        dbLogMsg += "Old val: " + std::to_string(globalStatsEarly[i]) + " ---> " + std::to_string(newGlobalStats[i]) + "\n";
    }

    dbLogMsg += "Old val: " + std::to_string(oldRatio) + " ---> " + std::to_string(newRatio) + "\n";

    dbLogMsg += "Saving values in following format: \n";
    
    for(auto i = 0; i < globalStatsEarly.size(); i++)
    {
        dbLogMsg += "Value: " + std::to_string(globalStatsEarly[i] + newGlobalStats[i]) + "\n";
    }

    dbLogMsg += "Value: " + std::to_string(oldRatio + newRatio);

    return dbLogMsg;
}


// Turn

 const std::string DebugLogger::dbLogGameTurnSumPlayerWonMoney(const std::string& playerName, const int& currentMoney, const int& wonAmmount)
 {
    std::string dbLogMsg = dbLogGameTurnSummaryPhase + "Player: " + playerName + ": WonMoney\n";
    dbLogMsg += "Curr: " + std::to_string(currentMoney) + " ---> " + std::to_string(wonAmmount) + "\n";
    dbLogMsg += " NewVal: " + std::to_string(currentMoney + wonAmmount);
    return dbLogMsg;
 }

 const std::string DebugLogger::dbLogGameTurnSumPlayerNotWonMoney(const std::string& playerName, const int& currentMoney, const int& lostMoney)
 {
    std::string dbLogMsg = dbLogGameTurnSummaryPhase + "Player: " + playerName + ": WonMoney\n";
    dbLogMsg += "Curr: " + std::to_string(currentMoney) + " <--- " + std::to_string(lostMoney);
    dbLogMsg += " NewVal: " + std::to_string(currentMoney - lostMoney);
    return dbLogMsg;
 }

// Logger

const std::string DebugLogger::dbLogLoggerGetMessage(const std::string& plainLog)
{
    return helperDbLogPlainFlow + plainLog;
}

DebugLogger::~DebugLogger()
{
    addDebugLog({dbLogAppCloses});
    buildDebugLogs();

    if(debugFile_.is_open())
    {
        debugFile_.close();
    }

}