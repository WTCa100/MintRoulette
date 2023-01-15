#pragma once

#include <string>
#include <map>

#include "./Paths.h"

/// @brief This map stores all the information about every file necessery to launch the game.
/// @note Every file added or deleted must be stored here along with its path
/// @warning Init.cfg is not included in this list
/// @details Map stores information about the following: expected file path (key value); file name decleared as pair (second value)
std::map<const std::string, const std::string> _filesToCheck{

};

class FileManager{
    public:
    bool isFileGood(const std::string& path, const std::string& fileName);
    void createFile(const std::string& path, const std::string& filename);

    FileManager() = default;
};