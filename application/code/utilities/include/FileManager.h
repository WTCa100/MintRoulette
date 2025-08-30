#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>
#include <sys/stat.h>

#include "./Paths.h"
#include "../../game/include/Player.h"
#include "../include/DebugLogger.h"



enum FileType{
    PlayerStat  = 1,
    GameSave    = 2,
    ProgramSaveDbg = 3,
    AiNameList  = 4,
    Highscores  = 5
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

    /// @brief This map stores all the information about every file necessery to launch the game.
    /// @note Every file added or deleted must be stored here along with its path
    /// @warning Init.cfg is not included in this list
    /// @details Map stores information about the following: fileType (key value), expected file path file name decleared as pair (second value)
    std::map<const FileType, const std::pair<const std::string, const std::string>> _filesToCheck{
        std::pair<const FileType, const std::pair<const std::string, const std::string>>(FileType::Highscores,
                                                                                      std::pair<std::string, std::string>(FILE_PLAYER_HIGHSCORES_PATH, FILE_PLAYER_HIGHSCORES)),
        std::pair<const FileType, const std::pair<const std::string, const std::string>>(FileType::AiNameList,
                                                                                      std::pair<std::string, std::string>(FILE_AI_NAME_LIST_PATH, FILE_AI_NAME_LIST))                                                                                      
    };

    bool isFileGood(const std::string& path, const std::string& fileName);
    void createFile(const std::string& path, const std::string& fileName);

    // Touch function is used to create already presseted file 
    void touch(const FileType& fTypem, const std::string& fileName);
    void checkFiles();
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
    bool alreadyInHighscores(const std::string& playerName, std::vector<std::pair<double, std::string>> highscores);
    std::vector<std::pair<double, std::string>> loadHighscores();
    void updateHighscores(std::vector<std::pair<double, std::string>> highscores);

    FileManager() = default;
    FileManager(DebugLogger* dbLog);
    ~FileManager();

    private:
    DebugLogger* dbgLog_;
};