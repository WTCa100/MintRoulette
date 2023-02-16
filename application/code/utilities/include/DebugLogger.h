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
    const std::string dbLogClassPlayerDestruct = "Debug: Application: Class: Player: Destruct";
    const std::string dbLogClassTurnInitialize = "Debug: Application: Class: Turn: Initialize";
    const std::string dbLogClassTurnDestruct = "Debug: Application: Class: Turn: Destruct";
    const std::string dbLogClassBetInitialize = "Debug: Application: Class: Bet: Initialize";
    const std::string dbLogClassBetDestruct = "Debug: Application: Class: Bet: Destruct";
    const std::string dbLogClassAiInitialize = "Debug: Application: Class: Ai: Initialize";
    const std::string dbLogClassAiDestruct = "Debug: Application: Class: Ai: Destruct";

    // Universals
    const std::string helperDbLogBoolResult(const std::string& msgPath, const bool& checkResult);
    const std::string helperDbLogLoopStringVector(const std::string& msgPath, const std::vector<std::string>& interateThrough);
    const std::string helperDbLogVectorEmpty(const std::string& msgPath, const std::vector<std::string>& checkVector);
    const std::string helperDbLogAddContentToFile(const std::string& msgPath, const std::string& path, const std::string& fileName, const std::string& content);
    const std::string helperDbLogCheckUserInput(const std::string& msgPath, const std::string& userInput, const bool& result);
    const std::string helperDbLogMapValues(const std::string& msgPath, const std::string& valueFirst, const std::string& valueSecond)
        { return msgPath + "Mapped: " + valueFirst + " With: " + valueSecond; }
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
    const std::string dbLogMenuMainPlayerList = helperDbLogPositionMenu + "MainPlayerList";
    const std::string dbLogMenuMainPlayerListChooseDetails = dbLogMenuMainPlayerList + "Choose: Detailed Record";
    const std::string dbLogMenuMainPlayerListAttemptToShowDetails(const std::string& player)
        { return dbLogMenuMainPlayerListChooseDetails + ": Player: " + player; }
    const std::string dbLogMenuMainGameList = helperDbLogPositionMenu + "MainGameList";
    const std::string dbLogMenuMainGameListChooseDetails = dbLogMenuMainGameList + "Choose: Detailed Record";
    const std::string dbLogMenuMainGameListDisplay(const std::vector<std::string>& games);

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
    const std::string dbLogGamePushPlayers(const std::string& nickname, const int& vecsSize)
        { return dbLogGameSetPlayerNameSection + ": " + nickname + ": Add: To: players_: "; }
    const std::string dbLogGameSetPlayerAliveVector = dbLogGameSetPlayerNameSection + ": players_: Assign: To: playersAlive_";
    const std::string dbLogGamePushPlayersEliminated(const std::string& nickname, const int& vecsSize)
        { return dbLogGameSetPlayerNameSection + ": " + nickname + ": Add: To: playersEliminated_: "; }
    const std::string dbLogGameEraseEliminatedPlayers(const std::string& nickname, const int& vecsSize)
        { return dbLogGameSetPlayerNameSection + ":" + nickname + ": Kill New vector size: " + std::to_string(vecsSize); }
    const std::string dbLogGamePushTurn(const int& vecsSize)
        { return helperDbLogPositionGame + "Turn: PushBack: NewSize: " + std::to_string(vecsSize); }
    const std::string dbLogGameInsertBetsAndPlayer(const int& vecsSize)
        { return helperDbLogPositionGame + "Bets: Insert: NewSize: " + std::to_string(vecsSize); }
    const std::string dbLogGameCheckConditionsIfEndEarly(const bool& endEarly)
        { return helperDbLogBoolResult(helperDbLogPositionGame + "Flow: Check if conditions to stop early are met ", endEarly); }
    const std::string dbLogGameFlowStarts = helperDbLogPositionGame + "Flow: Starts";
    const std::string dbLogGameFlowEnds = helperDbLogPositionGame + "Flow: Ends";
    const std::string dbLogGameFlowEndsSummary = dbLogGameFlowEnds + ": Summary";

    // Player 
    const std::string helperDbLogPositionGameSpecifiedPlayer(const std::string& playerName)
    { return helperDbLogPositionGame + "Player: Name: " + playerName + ": "; } 
    const std::string helperDbLogPositionGamePlayer = helperDbLogPositionGame + "Player: ";
    const std::string dbLogPlayerInitializedValues(const std::string& nickName = "", const int& globalMoneyAccumulated = 0,
                                                   const int& globalMoneyLost = 0, const int& globalGoodBetCount = 0,
                                                   const int& globalBetCount = 0, const int& globalPassCount = 0,
                                                   const int& balance = 0,  const double& globalGoodBetRatio = 0.0, 
                                                   const int& playerOrder = 0, const bool& isBot = 0);
    const std::string dbLogPlayerSetNickname(const std::string& playerName)
        { return helperDbLogPositionGamePlayer + "Name: Set: " + playerName; }
    const std::string dbLogPlayerSetBetCount(const std::string& playerName, const int& newBetCount)
        { return helperDbLogPositionGameSpecifiedPlayer(playerName) + "Bet: Count: Set: " + std::to_string(newBetCount); }
    const std::string dbLogPlayerSetPassCount(const std::string& playerName, const int& newPassCount)
        { return helperDbLogPositionGameSpecifiedPlayer(playerName) + "Bet: Pass: Count: Set: " + std::to_string(newPassCount); }      
    const std::string dbLogGamePlayerMoveToGlobal(const std::string& nickName, std::vector<int> globalStatsEarly, std::vector<int> newGlobalStats, const double& oldRatio);


    // Turn
    const std::string helperDbLogPositionGameTurn = helperDbLogPositionGame + "Turn: ";
    const std::string dbLogGameTurnIdStarts(const int& turnId)
        { return helperDbLogPositionGameTurn + "With: Id: " + std::to_string(turnId) + " Starts"; }
    const std::string dbLogGameTurnIdEnd(const int& turnId)
        { return helperDbLogPositionGameTurn + "With: Id: " + std::to_string(turnId) + " Ends"; }    
    const std::string dbLogGameTurnBettingPhase = helperDbLogPositionGameTurn + " BettingPhase: ";
    const std::string dbLogGameTurnShowPlayer(const std::string& nickname, const int& bankBalance, const bool& isBot)
        { return dbLogGameTurnBettingPhase + "Turn: " + nickname + ": BankBalance: " + std::to_string(bankBalance) + ": IsBot: " + std::to_string(isBot); }
    const std::string dbLogGameTurnAskForBet(const std::string& nickname)
        { return dbLogGameTurnBettingPhase + nickname + ": AskForBet"; }
    const std::string helperDbLogPositionGameTurnGetInput = helperDbLogPositionGameTurn + "Get: Input";
    const std::string dbLogGameTurnGetInput = helperDbLogPositionGameTurnGetInput;
    const std::string dbLogGameTurnGetInputResult(const std::string& userInput, const bool& result)
        { return helperDbLogCheckUserInput(helperDbLogPositionGameTurnGetInput, userInput, result); }
    const std::string dbLogGameTurnMapUserWithBetValues(const std::string& userName, const std::string& betType)
        { return helperDbLogMapValues(dbLogGameTurnBettingPhase, userName, betType); }
    const std::string dbLogGameTurnPlayerEnd(const std::string& userTurn)
        { return dbLogGameTurnBettingPhase + "Turn: " + userTurn + ": Has ended"; }
    const std::string dbLogGameTurnRollTheRoulettePhase = helperDbLogPositionGameTurn + " RollPhase: ";
    const std::string dbLogGameTurnRollTheGetRandomNumber(const int& randomNumber)
        { return dbLogGameTurnRollTheRoulettePhase + "Generate: RandomNumber: " + std::to_string(randomNumber); }    
    const std::string dbLogGameTurnRollSetLuckyNumber(const int& luckyNumber)
        { return dbLogGameTurnRollTheRoulettePhase + "LuckyNumber: Set: " + std::to_string(luckyNumber); }
    const std::string dbLogGameTurnSummaryPhase = helperDbLogPositionGameTurn + " SummaryPhase: ";
    const std::string dbLogGameTurnSumPlayerWonMoney(const std::string& playerName, const int& currentMoney, const int& wonAmmount);
    const std::string dbLogGameTurnSumPlayerNotWonMoney(const std::string&, const int& currentMoney, const int& moneyLost);

    // Bet
    const std::string helperDbLogPositionGameTurnBet = helperDbLogPositionGameTurn + "Bet: ";
    const std::string dbLogGaneTurnBetBetBuild = helperDbLogPositionGameTurnBet + "Build: ";
    const std::string helperDbLogPositionGameTurnBetGetInput = helperDbLogPositionGameTurnBet + "Get: Input: ";
    const std::string dbLogGameTurnBetBuildGetInput = helperDbLogPositionGameTurnBetGetInput;
    const std::string dbLogGameTurnBetBuildGetInputResult(const std::string& userInput, const bool& result)
        { return helperDbLogCheckUserInput(helperDbLogPositionGameTurnBetGetInput, userInput, result); }
    const std::string dbLogGameTurnBetBuildObtainAmmountBetted = dbLogGaneTurnBetBetBuild + "AmmountBetted: ";
    const std::string dbLogGameTurnBetBuildSetAmmountBetted(const int& ammount)
        { return dbLogGameTurnBetBuildObtainAmmountBetted + "Set: " + std::to_string(ammount); }
    const std::string dbLogGameTurnBetBuildObtainBetType = dbLogGaneTurnBetBetBuild + "BetType: ";
    const std::string dbLogGameTurnBetBuildSetBetType(const std::string& betType)
        { return dbLogGameTurnBetBuildObtainBetType + "Set" + betType; }
    const std::string dbLogGameTurnBetBuildBetTypeWinningOdds(const std::string& betType, const double& winningOds)
        { return dbLogGameTurnBetBuildObtainBetType + betType + ": WinningOdd: " + std::to_string(winningOds); }
    const std::string dbLogGameTurnBetGetDetails = dbLogGaneTurnBetBetBuild +" Get: Details";
    const std::string dbLogGameTurnBetBuildBetStraightUpSet(const std::string& nickname, const int& luckNumber)
        { return dbLogGameTurnBetBuildObtainBetType + "StraightUp: Player: Name: " + nickname + ": Choosen: " + std::to_string(luckNumber); }
    const std::string dbLogGameTurnBetBuildBetDozenSet(const std::string& nickname, const std::string& numberRange)
        { return dbLogGameTurnBetBuildObtainBetType + "DozenBet: Player: Name: " + nickname + ": Choosen: " + numberRange; }
    const std::string dbLogGameTurnBetBuildBetIsOddChoosenSet(const std::string& nickname, const bool& isOddChoosen)
        { return helperDbLogBoolResult(dbLogGameTurnBetBuildObtainBetType + "StraightUp: Player: Name: " + nickname + ": Choosen: IsOdd: ", isOddChoosen); }
    const std::string dbLogGameTurnBetPlayerPassed(const std::string& playerName)
        { return helperDbLogPositionGameTurnBet + playerName + ": " + "Passed "; }
    const std::string dbLogGameTurnBetIsBetGood(const std::string& playerName,  const bool& isBetGood)
        { return helperDbLogBoolResult(helperDbLogPositionGameTurnBet + "Player: " + playerName + ": IsBetGood: ", isBetGood); }

    // Ai
    const std::string helperDbLogPositionGameTurnBetAi = helperDbLogPositionGameTurnBet + "Ai: ";
    const std::string dbLogGameTurnBetAiGeneratedSeed(const int& seed)
        { return helperDbLogPositionGameTurnBetAi + "Seed: " + std::to_string(seed); }
    const std::string dbLogGameTurnBetAiChooseActionWithBalance(const int& balance)
        { return helperDbLogPositionGameTurnBetAi + "Action: Choose: With Balance " + std::to_string(balance);}
    const std::string dbLogGameTurnBetAiChooseActionWithBalanceResult(const bool& result, const int& balance)
        { return helperDbLogBoolResult(dbLogGameTurnBetAiChooseActionWithBalance(balance), result); }

    
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