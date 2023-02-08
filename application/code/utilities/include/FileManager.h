#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>
#include <sys/stat.h>

#include "./Paths.h"
#include "../../game/include/Player.h"

/*
/// @brief This map stores all the information about every file necessery to launch the game.
/// @note Every file added or deleted must be stored here along with its path
/// @warning Init.cfg is not included in this list
/// @details Map stores information about the following: expected file path (key value); file name decleared as pair (second value)
std::map<const std::string, const std::string> _filesToCheck{

};*/

enum FileType{
    PlayerStat  = 1,
    GameSave    = 2,
    GameSaveDbg = 3,
    AiNameList  = 4
};


enum PlayerAttribute{
    plName             = 0,
    plGoodBetCount     = 1,
    plPassCount        = 2,
    plBetCount         = 3,
    plTotalMoneyGained = 4,
    plTotalMoneyLost   = 5,
    plGoodBetRatio     = 6
};

class FileManager{
    public:
    bool isFileGood(const std::string& path, const std::string& fileName);
    void createFile(const std::string& path, const std::string& fileName);

    // Touch function is used to create already presseted file 
    void touch(const FileType& fTypem, const std::string& fileName);
    void appendPlayerSaveFile(const Player& appPlayerStat);
    std::vector <std::string> loadFileContent(const std::string& path, const std::string& fileName);
    Player* makePlayerFromLoadedFile(const std::string& name,
                                     const uint16_t playerNumber = 0, 
                                     const uint32_t initialBankBalance = 0);
    void iterateGameIdConfig(const uint16_t& nextGameId);
    std::vector<std::string> loadFilesFromPath(const std::string path);
    std::vector<std::string> makeFileContentUnique(std::vector<std::string> fileContent);
    std::string trimPath(const std::string& rawFile);
    bool isEntryFolder(const std::string& path);
    uint16_t nextGameSaveId();
    std::string extractConfigValueFromTag(const std::string& tag);
    void changeConfigTagValue(const std::string& tag, const std::string& newValue);

    FileManager() = default;
};