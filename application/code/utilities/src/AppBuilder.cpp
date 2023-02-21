#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <algorithm>

#include "../include/AppBuilder.h"
#include "../include/Paths.h"


/// @brief Creates directory using "mkdir" command
/// @param pathToSet desired path to be created
/// @warning This function can result in infinite loop if not used properly
void AppBuilder::createDirectory(const std::string& pathToSet)
{
    const std::string sysCommandExec = "mkdir " + pathToSet;
    do
    {
        std::cout << sysCommandExec << std::endl;
        system(sysCommandExec.c_str());
    }while(!isDirectoryGood(pathToSet));

    dbLog_->addDebugLog(
        {dbLog_->dbLogAppBuilderCreateFolder(pathToSet)}
    );
    dbLog_->buildDebugLogs();

    std::cout << "Done!\n";
}

/// @brief Checks if directory exists using struct stat
/// @param path path to check
/// @return value of file stat
bool AppBuilder::isDirectoryGood(const std::string& path)
{
    struct stat buffer;

    dbLog_->addDebugLog(
        {dbLog_->dbLogAppBuilderCheckFolder(path),
         dbLog_->dbLogAppBuilderCheckFolderResult((stat(path.c_str(), &buffer) == 0))}
    );

    dbLog_->buildDebugLogs();

    return (stat(path.c_str(), &buffer) == 0);
}

/// @brief Check every path entry in _pathsToCheck
void AppBuilder::checkDirectories()
{
    // Check if there are no paths to check 
    if(_pathsToCheck.empty())
    {
        std::cout << "Nothing to check!\n";
        return;
    }

    // Check and create if necessery a folder
    for(auto path: _pathsToCheck)
    {
        std::cout << "Checking " << path << " ...\n";
        if(!isDirectoryGood(path))
        {
            std::cout << "Not found!\n";
            std::cout << "Attempting to create " << path << std::endl;
            createDirectory(path);
            continue;
        }
        
        std::cout << "Found!\n";
    }
}

/// @brief 
void AppBuilder::buildInitConfig()
{
    // Handle next game ID
    std::vector<std::string> potentialGameSaves;
    if(isDirectoryGood(FILE_GAME_SAVE_LOG_PATH))
    {
        potentialGameSaves = fileMgmt_->loadFilesFromPath(FILE_GAME_SAVE_LOG_PATH);
    }

    std::vector<uint16_t>* potentialGameSavesId = new std::vector<uint16_t>;

    dbLog_->addDebugLog(
        {dbLog_->dbLogAppBuilderInitConfigPotentialGameListEmpty(potentialGameSaves)}
    );

    dbLog_->buildDebugLogs();

    if(!potentialGameSaves.empty())
    {
        dbLog_->addDebugLog(
            {dbLog_->dbLogAppBuilderInitConfigPotentialGameListShow(potentialGameSaves)}
        );

        for(const auto entry : potentialGameSaves)
        {
            if(fileMgmt_->isEntryFolder(entry))
            {
                continue;
            }

            std::cout << entry << std::endl;
            std::string gameId = fileMgmt_->trimPath(entry);
            gameId.erase(gameId.begin(), gameId.begin() + 6);
            potentialGameSavesId->push_back(std::stoi(gameId));

        }
    }

    uint16_t nextGameId = 1;


    if(!potentialGameSavesId->empty())
    {
        nextGameId = fileMgmt_->nextGameSaveId();
    }

    dbLog_->addDebugLog(
        {dbLog_->dbLogAppBuilderInitConfigNextGameIdSet(nextGameId)}
    );

    dbLog_->buildDebugLogs();
    // Handle game version
    std::string gameVersion = "";

    if(fileMgmt_->isFileGood(FILE_VERSION_PATH, FILE_VERSION))
    {
        std::vector<std::string> gameVersionContent = fileMgmt_->loadFileContent(FILE_VERSION_PATH, FILE_VERSION);

        dbLog_->addDebugLog(
            {dbLog_->dbLogFManagerLoadFilesContentEmpty(FILE_VERSION_PATH, FILE_VERSION, gameVersionContent),
             dbLog_->dbLogFManagerLoadFilesContent(FILE_VERSION_PATH, FILE_VERSION, gameVersionContent)}
        );

        dbLog_->buildDebugLogs();

        if(!gameVersionContent.empty())
        {
            for(int i = 0; i < gameVersionContent.size(); i++)
            {
                std::cout << gameVersionContent[i] << std::endl;
                if(gameVersionContent[i].find("gameVersion:") != std::string::npos)
                {
                    std::string tmp = gameVersionContent[i];
                    std::cout << tmp << std::endl;
                    tmp.erase(tmp.begin(), tmp.begin() + tmp.rfind(":") + 1);
                    std::cout << tmp << std::endl;
                    gameVersion = tmp;
                    std::cout << gameVersion << std::endl;

                }

            }

            dbLog_->addDebugLog(
                {dbLog_->dbLogFManagerLoadFilesContentExtractedGameVersion(gameVersion)}
            );
        }
        else
        {
            gameVersion = "1.0.0";
        }
        
    }
    else
    {
        std::cout << "No game.version file found! Cannot properly load game version\n";
        gameVersion = "1.0.0";
    }

    dbLog_->addDebugLog(
        {dbLog_->dbLogAppBuilderInitConfigGameVersion(gameVersion)}
    );

    dbLog_->buildDebugLogs();


    // Build game config
    dbLog_->addDebugLog(
        {dbLog_->dbLogAppBuilderInitConfigBuild}
    );

    std::string initConfigPath = INIT_CONFIG_PATH;
    std::fstream initConfig;
    initConfig.open(initConfigPath + "/" + INIT_CONFIG_FILE);
    if(initConfig.is_open())
    {
        dbLog_->addDebugLog(
            {dbLog_->dbLogAppBuilderInitConfigAddContent(initConfigPath, INIT_CONFIG_FILE, "isInit         :1"),
             dbLog_->dbLogAppBuilderInitConfigAddContent(initConfigPath, INIT_CONFIG_FILE, "NextGameNumber :" + std::to_string(nextGameId)),
             dbLog_->dbLogAppBuilderInitConfigAddContent(initConfigPath, INIT_CONFIG_FILE, "gameVersion    :" + gameVersion),
             dbLog_->dbLogAppBuilderInitConfigAddContent(initConfigPath, INIT_CONFIG_FILE, "dummy          :text")}
        );

        initConfig << "isInit         :1\n";
        initConfig << "NextGameNumber :" + std::to_string(nextGameId) + "\n";
        initConfig << "gameVersion    :" + gameVersion + "\n";
        initConfig << "dummy          :text\n";
    }
    else
    {
        std::cout << "Could not open " << initConfigPath << " !" <<std::endl;
    }

    dbLog_->buildDebugLogs();
    
    delete potentialGameSavesId;


    initConfig.close();
}

/// @brief Creates every folder and file needed to play the game
void AppBuilder::setupGameFiles()
{
    isInitLaunch_ = isInitRequired();
    dbLog_->addDebugLog(
        {dbLog_->dbLogAppBuilderIsInitLaunch(isInitLaunch_)}
    );

    if(isInitLaunch_)
    {
        // If initial launch we need to create files first
        dbLog_->addDebugLog(
            {dbLog_->dbLogAppBuilderFolderCheckList(_pathsToCheck)}
        );
        dbLog_->buildDebugLogs();

        for(auto path : _pathsToCheck)
        {
            createDirectory(path);
        }
        // It's always safe to double check
        checkDirectories();
        fileMgmt_->createFile(INIT_CONFIG_PATH, INIT_CONFIG_FILE);
        buildInitConfig();
        
        // Check files
        for(auto file : fileMgmt_->_filesToCheck)
        {
            fileMgmt_->touch(file.first, file.second.second);
        }

        fileMgmt_->checkFiles();
        fileMgmt_->changeConfigTagValue("isInit", "0");
    }
    else
    {
        // Only check required
        checkDirectories();
        fileMgmt_->checkFiles();
        fileMgmt_->iterateGameIdConfig(fileMgmt_->nextGameSaveId());
    }

}

/// @todo Make this function also check if config states whether or not init setup is necessery
/// @brief Check if initial setup is required
/// @return State of init.cfg file
bool AppBuilder::isInitRequired()
{
    if(!fileMgmt_->isFileGood(INIT_CONFIG_PATH, INIT_CONFIG_FILE))
    {
        return true;
    }

    return (fileMgmt_->extractConfigValueFromTag("isInit") == "1");
}


/// @brief Initializes new FileManager and by default sets inital launch to true
AppBuilder::AppBuilder(DebugLogger* dbLog)
{

    dbLog_ = dbLog;

    // Prioritize making debug folder
    if(!isDirectoryGood("debug/"))
    {
        createDirectory("debug\\");
    }

    // Debug Logger
    {
        dbLog_->addDebugLog(
            {dbLog->dbLogClassAppBuilderInitialize}
        );
        dbLog_->touchDbLog();
        dbLog_->buildDebugLogs();
    }

    fileMgmt_ = new FileManager(dbLog_);
    isInitLaunch_ = true;
}

/// @brief Delete existing file manager instance
AppBuilder::~AppBuilder()
{
    //Debug Logger
    {
        dbLog_->addDebugLog(
            {dbLog_->dbLogClassAppBuilderDestruct}
        );

        dbLog_->buildDebugLogs();
    }

    system("cls");

    delete fileMgmt_;
}