#pragma once

#include <string>
#include <map>

#include "./Paths.h"

/// @brief This vector contains information about every directory AppBuilder class have to check.
/// Every addition or deletion of directories must be included here as well as in Paths.h
/// First Value: Path to check, Second Value: Setup path
static const std::map<std::string, std::string> _pathCheckingMap{
    std::pair(FOLDER_BIN, FOLDER_BIN_SETUP),
    std::pair(FOLDER_BIN_SAVES, FOLDER_BIN_SAVES_SETUP),
    std::pair(FOLDER_BIN_PLAYERS_STATS, FOLDER_BIN_PLAYERS_STATS_SETUP)
};


class AppBuilder
{
    public:
    void checkDirectories();
    void createDirectory(const std::pair<std::string, std::string>& setupPath);
    bool isDirectoryGood(const std::string& path);
};