#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <set>

class DebugLogger
{
public:
    // Operate on logging engine
    void addDebugLog(std::vector<std::string> logMessages);
    std::string dbLogAddTimeStamp();
    void buildDebugLogs();
    void touchDbLog();
    
    // Log messages
    const std::string dbLogTestMessage = "This is a test message";
    // App start/close
    const std::string dbLogAppOpen = "Debug: Application: Opens";
    const std::string dbLogAppCloses = "Debug: Application: Closes";
    // Class initializers / deconstructors
    const std::string dbLogClassAppBuilderInitialize = "Debug: Application: Class: AppBuilder: Initialize";
    const std::string dbLogClassAppBuilderDestruct = "Debug: Application: Class: AppBuilder: Destruction";
    const std::string dbLogClassFManagerInitialize = "Debug: Application: Class: FileManager: Initialize";
    const std::string dbLogClassFManageDestruct = "Debug: Application: Class: FileManager: Destruction";
    const std::string dbLogClassMenuInitialize = "Debug: Application: Class: Menu: Initialize";
    const std::string dbLogClassMenuDestruct = "Debug: Application: Class: Menu: Destruct";
    const std::string dbLogClassGameInitialize = "Debug: Application: Class: Game: Initialize";
    const std::string dbLogClassGameDestruct = "Debug: Application: Class: Game: Destruct";
    const std::string dbLogClassPlayerInitialize = "Debug: Application: Class: Player: Initialize";
    const std::string dbLogClassPlayerDestruct = "Debug: Application: Class: Player: Initialize";

    // Universals
    const std::string helperDbLogBoolResult(const std::string& msgPath, const bool& checkResult);
    const std::string helperDbLogLoopStringVector(const std::string& msgPath, const std::vector<std::string>& interateThrough);
    const std::string helperDbLogVectorEmpty(const std::string& msgPath, const std::vector<std::string>& checkVector);
    const std::string helperDbLogAddContentToFile(const std::string& msgPath, const std::string& path, const std::string& fileName, const std::string& content);
    const std::string helperDbLogCheckUserInput(const std::string& msgPath, const std::string& userInput, const bool& result);
    // App Builder substance logs
    // Folder check/create
    const std::string helperDbLogPositionAppBuilderFolder = "Debug: Application: AppBuilder: Folder: ";
    const std::string dbLogAppBuilderFolderCheckList(std::set<std::string> foldersToCheck);
    const std::string dbLogAppBuilderCheckFolder(const std::string& folder);
    const std::string dbLogAppBuilderCheckFolderResult(const bool& checkResult);
    const std::string dbLogAppBuilderCreateFolder(const std::string& folder);
    // Init building and checking
    const std::string helperDbLogPositionAppBuilderSetup = "Debug: Application: AppBuilder: Setup: ";
    const std::string dbLogAppBuilderIsInitLaunch(const bool& checkResult);
    const std::string dbLogAppBuilderInitConfigCreation = helperDbLogPositionAppBuilderSetup + "Create: Init.cfg: ";
    const std::string dbLogAppBuilderInitConfigPotentialGameListEmpty(const std::vector<std::string> checkVector);
    const std::string dbLogAppBuilderInitConfigPotentialGameListShow(const std::vector<std::string>& gameList);
    const std::string dbLogAppBuilderInitConfigNextGameIdSet(const int& nextGameId);
    const std::string dbLogAppBuilderInitConfigGameVersion(const std::string& gameVersion);
    const std::string dbLogAppBuilderInitConfigBuild = helperDbLogPositionAppBuilderSetup + "Init.cfg: Build ";
    const std::string dbLogAppBuilderInitConfigAddContent(const std::string& path, const std::string& fileName, const std::string& content);

    // File Manager substance logs
    // File check/create/touch
    const std::string helperDbLogPositionFManagerFiles = "Debug: Application: FileManager: File: ";
    const std::string dbLogFmanagerCheckForFile(const std::string& path, const std::string& fileName);
    const std::string dbLogFManagerCheckForFileResult(const std::string& path, const std::string& filename, const bool& checkResult);
    const std::string dbLogFManagerCreateFile(const std::string& path, const std::string& filename);
    const std::string dbLogFManagerTouchFile(const std::string& type, const std::string& path, const std::string& filename);
    const std::string dbLogFManagerFileAddContent(const std::string& path, const std::string& fileName, const std::string& content);
    // Loading files from path
    const std::string helperDbLogPositionFManagerLoadFilesFromPath = "Debug: Application: FileManager: File: Load: ";
    const std::string dbLogFManagerLoadFilesFromPath(const std::string& path);
    const std::string dbLogFManagerLoadFilesFromPathResult(const std::string& path, const std::vector<std::string>& filesList);
    const std::string dbLogFManagerLoadFilesContent(const std::string& path, const std::string& filename, const std::vector<std::string> contents);
    const std::string dbLogFManagerLoadFilesContentEmpty(const std::string& path, const std::string& filename, const std::vector<std::string> checkVector);
    const std::string dbLogFManagerLoadFilesContentExtractedGameVersion(const std::string& version)
        { return helperDbLogPositionFManagerLoadFilesFromPath + "Content: GameVersion: " + version;}
    // Operations on Init.cfg
    const std::string helperDbLogPositionFManagerInitConfig = helperDbLogPositionFManagerFiles + "Init.cfg: ";
    const std::string dbLogFManagerInitConfigEditTag(const std::string& tag, const std::string& newValue);
    const std::string dbLogFManagerInitConfigIterateGameId = helperDbLogPositionFManagerInitConfig + " Iterate Game Id";
    const std::string dbLogFManagerInitConfigGetNameSaveId(const int& nextGameId)
        { return helperDbLogPositionFManagerInitConfig + "NextGameId: " + std::to_string(nextGameId);}
    // Create player from file
    const std::string helperDbLogPositionFManagerMakePlayer = "Debug: Application: FileManager: Player: Make: ";
    const std::string dbLogFMangagerMakePlayerWithValues(const std::string& playerName, const int& playerId, const int& bankBalance)
        { return helperDbLogPositionFManagerMakePlayer + "Name: " + playerName + " Id: " + std::to_string(playerId) + " BankBalance: " + std::to_string(bankBalance); }

    // Menu substance logs
    const std::string helperDbLogPositionMenu = "Debug: Application: Menu: ";
    const std::string dbLogMenuMainMenuDisplay = helperDbLogPositionMenu + "Display: MainMenu";
    const std::string dbLogMenuGetInput = helperDbLogPositionMenu + "Get: Input";
    const std::string dbLogMenuCheckUserInput(const std::string& userInput, const bool& isGood);
    const std::string dbLogMenuChoosenOption(const std::string& choosenOption)
        { return helperDbLogPositionMenu + "Option: Choosen: " + choosenOption;}
    // Game Substance logs
    const std::string helperDbLogPositionGame = "Debug: Application: Game: ";
    const std::string helperDbLogPositionGameGetInput = helperDbLogPositionGame + "Get: Input";
    const std::string dbLogGameStartOfTheGame(const int& gameId)
        { return helperDbLogPositionGame + " Id: " + std::to_string(gameId) + ": Start"; }
    const std::string dbLogGameGetGameId = helperDbLogPositionGame + "Get: Id";
    const std::string dbLogGameGetGameIdObtained(const int& gameId)
        { return helperDbLogPositionGame + " Get: Id: Value: Received: " + std::to_string(gameId);}
    const std::string dbLogGameSetupConfig = helperDbLogPositionGame + "Setup: Config";
    const std::string dbLogGameGetInput = helperDbLogPositionGameGetInput;
    const std::string dbLogGameGetInputCheck(const std::string& userInput, const bool& result)
        { return helperDbLogCheckUserInput(helperDbLogPositionGameGetInput, userInput, result);}
    const std::string dbLogGamePlayerCountSet(const int& playerCount)
        { return dbLogGameSetupConfig + ": PlayerCount: Set: " + std::to_string(playerCount);}
    const std::string dbLogGameCheckForBots(const bool& areBotsAllowed)
        { return helperDbLogBoolResult(dbLogGameSetupConfig + "AreBotsAllowed: ", areBotsAllowed); }
    const std::string dbLogGameSetBotCount(const int& botCount)
        { return dbLogGameSetupConfig + ": BotCount: Set: " + std::to_string(botCount); }
    const std::string dbLogGameSetBankBalance(const int& bankBalance)
        { return dbLogGameSetupConfig + ": InitialBankBalance: Set: " + std::to_string(bankBalance); }
    const std::string dbLogGameSetPlayerNameSection = dbLogGameSetupConfig + "Player: Names: Setup";
    const std::string dbLogGameSetPlayerName(const std::string& playerName, const int& playerId)
        { return dbLogGameSetPlayerNameSection + ": Id:" + std::to_string(playerId) + " Nick: Set: " + playerName; }
    const std::string dbLogGameCheckIfPlayerExists(const std::string& playerName)
        { return dbLogGameSetupConfig + ": Player: Name: " + playerName + " Check: IfExists"; }
    const std::string dbLogGameIfPlayerExists(const std::string& playerName, const bool& result)
        { return helperDbLogBoolResult(dbLogGameSetupConfig + ": Player: Name: " + playerName + " Check: IfExists", result); }

    // Player 
    const std::string helperDbLogPositionGameSpecifiedPlayer = helperDbLogPositionGame + "Player: Name: ";
    const std::string helperDbLogPositionGamedPlayer = helperDbLogPositionGame + "Player: ";
    const std::string dbLogPlayerInitializedValues(const std::string& nickName = "", const int& globalMoneyAccumulated = 0,
                                                   const int& globalMoneyLost = 0, const int& globalGoodBetCount = 0,
                                                   const int& globalBetCount = 0, const int& globalPassCount = 0,
                                                   const int& balance = 0,  const double& globalGoodBetRatio = 0.0, 
                                                   const int& playerOrder = 0, const bool& isBot = 0);

    // Logger
    const std::string helperDbLogPlainFlow = "Debug: Application: Game: Game --> Log Msg: \n";
    const std::string dbLogLoggerGetMessage(const std::string& plainLog);

    DebugLogger();
    ~DebugLogger();

private:
    std::vector<std::string> logMessages_;
    std::string fileName_;
    std::fstream debugFile_;
};