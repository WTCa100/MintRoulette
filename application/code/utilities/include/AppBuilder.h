#pragma once

#include <string>
#include <vector>

#include "./Paths.h"


const std::vector<std::string> _pathsToCheck{
    FOLDER_BIN,
    FOLDER_BIN_SAVES,
    FOLDER_BIN_PLAYERS_STATS,
    FOLDER_BIN_UTILIS
};

class AppBuilder
{
    public:
    void checkDirectories();
    void createDirectory(const std::string& path);
    bool isDirectoryGood(const std::string& path);
};