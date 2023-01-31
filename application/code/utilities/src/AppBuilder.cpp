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
    std::cout << "Done!\n";
}

/// @brief Checks if directory exists using struct stat
/// @param path path to check
/// @return value of file stat
bool AppBuilder::isDirectoryGood(const std::string& path)
{
    struct stat buffer;
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
    // Check if any games already exists
    std::vector<std::string> potentialGameSaves;
    if(isDirectoryGood(FILE_GAME_SAVE_LOG_PATH))
    {
        potentialGameSaves = fileMgmt_->loadFilesFromPath(FILE_GAME_SAVE_LOG_PATH);
    }

    std::vector<uint16_t>* potentialGameSavesId = new std::vector<uint16_t>;
    if(!potentialGameSaves.empty())
    {
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
    else
    {
        delete potentialGameSavesId;
    }

    std::string initConfigPath = INIT_CONFIG_PATH;
    std::fstream initConfig;
    initConfig.open(initConfigPath + "/" + INIT_CONFIG_FILE);
    if(initConfig.is_open())
    {
        initConfig << "isInit         :1\n";
        initConfig << "NextGameNumber :" + std::to_string(nextGameId) + "\n";
        initConfig << "gameVersion    :0.1v\n";
        initConfig << "dummy          :text\n";
    }
    else
    {
        std::cout << "Could not open " << initConfigPath << " !" <<std::endl;
    }

    if(potentialGameSavesId)
    {
        delete potentialGameSavesId;
    }

    initConfig.close();
}

/// @brief Creates every folder and file needed to play the game
void AppBuilder::setupGameFiles()
{
    isInitLaunch_ = isInitRequired();
    std::cout << "Debug: Is initial launch: " << isInitLaunch_ << std::endl;
    if(isInitLaunch_)
    {
        // If initial launch we need to create files first
        for(auto path : _pathsToCheck)
        {
            createDirectory(path);
        }
        // It's always safe to double check
        checkDirectories();
        fileMgmt_->createFile(INIT_CONFIG_PATH, INIT_CONFIG_FILE);
        buildInitConfig();
        fileMgmt_->touch(FileType::AiNameList, FILE_AI_NAME_LIST);
    }
    else
    {
        // Only check required
        checkDirectories();
        if(!fileMgmt_->isFileGood(FILE_GAME_AI_NAME_LIST_PATH, FILE_AI_NAME_LIST))
        {
            fileMgmt_->touch(FileType::AiNameList, FILE_AI_NAME_LIST);    
        }
        fileMgmt_->iterateGameIdConfig(fileMgmt_->nextGameSaveId());
    }

}

/// @todo Make this function also check if config states whether or not init setup is necessery
/// @brief Check if initial setup is required
/// @return State of init.cfg file
bool AppBuilder::isInitRequired()
{
    return !fileMgmt_->isFileGood(INIT_CONFIG_PATH, INIT_CONFIG_FILE);
}


/// @brief Initializes new FileManager and by default sets inital launch to true
AppBuilder::AppBuilder()
{
    fileMgmt_ = new FileManager();
    isInitLaunch_ = true;
}

/// @brief Delete existing file manager instance
AppBuilder::~AppBuilder()
{
    delete fileMgmt_;
}