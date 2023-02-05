#pragma once

#include <string>
#include <set>
#include <map>

// Get header
#include "./Paths.h"
#include "./FileManager.h"

// Get source
#include "../src/FileManager.cpp"

/// @brief This set stores information about every folder that has to 
/// be created via AppBuilder.
/// @note This container take a role of enumerator.
const std::set<std::string> _pathsToCheck{
    FOLDER_BIN,
    FOLDER_BIN_SAVES,
    FOLDER_BIN_PLAYERS_STATS,
    FOLDER_BIN_SAVES_DEBUG,
    FOLDER_BIN_AI
};

const std::map<FileType, std::pair<std::string,  std::string>> _filesToCheck{
    {FileType::AiNameList, std::make_pair<std::string, std::string>(FILE_GAME_AI_NAME_LIST_PATH, FILE_AI_NAME_LIST)},
    {FileType::Highscores, std::make_pair<std::string, std::string>(FILE_PLAYER_HIGHSCORES_PATH, FILE_PLAYER_HIGHSCORES)}
};

class AppBuilder
{
    public:
    void setupGameFiles();
    bool isDirectoryGood(const std::string& path);

    AppBuilder();
    ~AppBuilder();

    protected:
    void buildInitConfig();

    void checkDirectories();

    void createDirectory(const std::string& path);

    bool isInitRequired();

    private:
    bool isInitLaunch_;
    FileManager* fileMgmt_;
};