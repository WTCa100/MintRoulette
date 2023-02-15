#pragma once

#include <string>
#include <set>
#include <map>

// Get header
#include "./Paths.h"
#include "./FileManager.h"
#include "./DebugLogger.h"

// Get source
#include "../src/FileManager.cpp"

/// @brief This set stores information about every folder that has to 
/// be created via AppBuilder.
/// @note This container take a role of enumerator.
const std::set<std::string> _pathsToCheck{
    FOLDER_BIN,
    FOLDER_BIN_SAVES,
    FOLDER_BIN_PLAYERS_STATS,
    FOLDER_DEBUG,
    FOLDER_BIN_AI
};

class AppBuilder
{
    public:
    void setupGameFiles();
    bool isDirectoryGood(const std::string& path);

    void createDirectory(const std::string& path);

    AppBuilder(DebugLogger* dbLog);
    ~AppBuilder();

    protected:
    void buildInitConfig();

    void checkDirectories();

    bool isInitRequired();

    private:
    DebugLogger* dbLog_;
    bool isInitLaunch_;
    FileManager* fileMgmt_;
};