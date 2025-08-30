#include <iostream> // For debug
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <experimental/filesystem>

#include "../include/FileManager.h"
#include "../include/NameList.h"

/// @brief Checks whether or not a provided file exists
/// @param path location of file 
/// @param fileName name of the file
/// @return File state
bool FileManager::isFileGood(const std::string& path, const std::string& fileName)
{

    std::ifstream fileCheck(path + "/" + fileName);
    
    dbgLog_->addDebugLog(
        {dbgLog_->dbLogFmanagerCheckForFile(path, fileName),
         dbgLog_->dbLogFManagerCheckForFileResult(path, fileName, fileCheck.good())}
    );
    dbgLog_->buildDebugLogs();

    return fileCheck.good();
}

/// @brief Creates file in given directory and nickname
/// @param path destination where file should be saved
/// @param fileName filename
void FileManager::createFile(const std::string& path, const std::string& fileName)
{
    const std::string toMake = path + "/" + fileName;
    std::ofstream makeFile;
    makeFile.open(toMake);
    if(makeFile.is_open())
    {
        std::cout << "Done!\n";
        return;
    }

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogFManagerCreateFile(path, fileName)}
    );

    dbgLog_->buildDebugLogs();
    
    std::cout << "Could not create the file!\n";
}

/// @brief Creates file using simple template.
/// @param fType file type that the file has
/// @param fileName desired name of the file
void FileManager::touch(const FileType& fType, const std::string& fileName)
{
    std::string tmpPathHolder;
    std::string filePath;
    std::ofstream makeFile;    
    std::set<std::string> nameOutput;
    switch (fType)
    {
    case PlayerStat:
        dbgLog_->addDebugLog(
            {dbgLog_->dbLogFManagerTouchFile("PlayerStat", FILE_PLAYER_STATS_PATH, fileName)}
        );

        createFile(FILE_PLAYER_STATS_PATH, fileName);
        tmpPathHolder = FILE_PLAYER_STATS_PATH;
        filePath = tmpPathHolder + "/" + fileName;
        makeFile.open(filePath);

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogFManagerFileAddContent(tmpPathHolder, fileName, "Name:\nGoodBetCount:\nPassCount:\nBetCount:\nTotalMoneyGained:\nTotalMoneyLost:\nGoodBetRatio:\n")}
        );

        makeFile << "Name:\nGoodBetCount:\nPassCount:\nBetCount:\nTotalMoneyGained:\nTotalMoneyLost:\nGoodBetRatio:\n";
        makeFile.close();
        break;
    case GameSave:

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogFManagerTouchFile("GameSave", FILE_GAME_SAVE_LOG_PATH, fileName + EXT_GAME_LOG)}
        );

        createFile(FILE_GAME_SAVE_LOG_PATH, "GameNr" + fileName + EXT_GAME_LOG);
        break;
    case ProgramSaveDbg:
        
        dbgLog_->addDebugLog(
            {dbgLog_->dbLogFManagerTouchFile("ProgramSaveDbg", FILE_GAME_DEBUG_LOG_DBG_PATH, fileName + EXT_PROGRAM_LOG_DEBUG)}
        );

        createFile(FILE_GAME_DEBUG_LOG_DBG_PATH, fileName + EXT_PROGRAM_LOG_DEBUG);
        break;
    case AiNameList:

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogFManagerTouchFile("AiNameList", FILE_GAME_AI_NAME_LIST_PATH, FILE_AI_NAME_LIST)}
        );

        createFile(FILE_GAME_AI_NAME_LIST_PATH, FILE_AI_NAME_LIST);
        tmpPathHolder = FILE_GAME_AI_NAME_LIST_PATH;
        filePath = tmpPathHolder + "/" + FILE_AI_NAME_LIST;
        makeFile.open(filePath);
        nameOutput = NameList::names;
        for(auto& name : nameOutput)
        {

            dbgLog_->addDebugLog(
                {dbgLog_->dbLogFManagerFileAddContent(tmpPathHolder, fileName, name)}
            );

            makeFile << name << std::endl;
        }
        makeFile.close();
        break;
    case Highscores:

        dbgLog_->addDebugLog(
            {dbgLog_->dbLogFManagerTouchFile("Highscores", FILE_PLAYER_HIGHSCORES_PATH, FILE_PLAYER_HIGHSCORES)}
        );

        createFile(FILE_PLAYER_HIGHSCORES_PATH, FILE_PLAYER_HIGHSCORES);
        tmpPathHolder = FILE_PLAYER_HIGHSCORES_PATH;
        filePath = tmpPathHolder + "/" + FILE_PLAYER_HIGHSCORES;
        makeFile.open(filePath);
        
        dbgLog_->addDebugLog(
            {dbgLog_->dbLogFManagerFileAddContent(tmpPathHolder, FILE_PLAYER_HIGHSCORES, "PlaceNo,BetRatio,Name")}
        );
                
        makeFile << "PlaceNo,BetRatio,Name\n";
        makeFile.close();
        break;
    default:
        std::cout << "No such file type in preset templates. Use createFile!\n";
        break;
    }
    
    dbgLog_->buildDebugLogs();

}

/// @brief Loads information about previous save state and append it with new values
/// @param appPlayerStat player whom values shall be updated
void FileManager::appendPlayerSaveFile(const Player& appPlayerStat)
{
    std::string path = FILE_PLAYER_STATS_PATH;
    std::vector<std::string> appendContent = loadFileContent(FILE_PLAYER_STATS_PATH, 
                                                             appPlayerStat.getNickName() + EXT_PLAYER_STATS);
    std::ofstream appendTheSave;
    appendTheSave.open(path + "/" + appPlayerStat.getNickName() + EXT_PLAYER_STATS);
    uint16_t lineNum = 0;

    for(auto& line : appendContent)
    {
        // Delete old values
        line.erase(line.begin() + line.rfind(':') + 1, line.end());
        // Add new values
        appendTheSave << line;
        switch (static_cast<PlayerAttribute>(lineNum))
        {
        case PlayerAttribute::plName:
            appendTheSave << appPlayerStat.getNickName();
            break;
        case PlayerAttribute::plGoodBetCount:
            appendTheSave << appPlayerStat.getGlobalGoodBetCount();
            break;            
        case PlayerAttribute::plPassCount:
            appendTheSave << appPlayerStat.getGlobalPassCount();
            break;            
        case PlayerAttribute::plBetCount:
            appendTheSave << appPlayerStat.getGlobalBetCount();
            break;            
        case PlayerAttribute::plTotalMoneyGained:
            appendTheSave << appPlayerStat.getGlobalMoneyAccumulated();
            break;
        case PlayerAttribute::plTotalMoneyLost:
            appendTheSave << appPlayerStat.getGlobalMoneyLost();
            break;    
        case PlayerAttribute::plGoodBetRatio:
            appendTheSave << appPlayerStat.getGlobalGoodBetRatio();
        default:
        // Eof
            break;
        }
        appendTheSave << std::endl;
        lineNum++;
    }
    appendTheSave.close();
}

/// @brief Loads content line by line into a vector
/// @param path path to the file
/// @param fileName which file at path to load
/// @return vector populated with read lines 
std::vector <std::string> FileManager::loadFileContent(const std::string& path, const std::string& fileName)
{
    std::vector<std::string> fileContent;
    std::ifstream readFile;
    std::string lineInfo;
    // No need to include EXT_PLAYER_STATS as it is already being passed with this
    readFile.open(path + "/" + fileName);
    if(!readFile.is_open())
    {
        std::cout << "Something went wrong!\n";
    }
    while(std::getline(readFile, lineInfo))
    {
        fileContent.push_back(lineInfo);
    }
    readFile.close();

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogFManagerLoadFilesContent(path, fileName, fileContent)}
    );

    dbgLog_->buildDebugLogs();

    return fileContent;
}

/// @brief Loads player attributes from save file and assings them to a player pointer
/// @param name loading player's name
/// @param initialBankBalance 
/// @return Player instance with setup values
Player* FileManager::makePlayerFromLoadedFile(const std::string& name,
                                              const uint16_t playerNumber,
                                              const uint32_t initialBankBalance)
{
    std::vector<std::string> playerValues = loadFileContent(FILE_PLAYER_STATS_PATH, name + EXT_PLAYER_STATS);

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogFMangagerMakePlayerWithValues(name, playerNumber, initialBankBalance)}
    );

    dbgLog_->buildDebugLogs();

    // Get Values
    for(auto& line : playerValues)
    {
        line.erase(line.begin(), line.begin() + line.rfind(':') + 1);
    }

    // Initialize temporary values
    uint32_t goodBetCount; uint32_t passCount; uint32_t betCount; int totalMoneyGained; int totalMoneyLost;
    double goodBetRatio;
    for(int attribute = 0; attribute < playerValues.size(); attribute++)
    {
        switch(static_cast<PlayerAttribute>(attribute))
        {
            // We already have the name so no need to do anythin here
            case PlayerAttribute::plName:
            continue;
            break;
            case PlayerAttribute::plGoodBetCount:
            goodBetCount = static_cast<uint32_t> (std::stoul(playerValues[attribute]));
            break;
            case PlayerAttribute::plPassCount:
            passCount = static_cast<uint32_t> (std::stoul(playerValues[attribute]));
            break;
            case PlayerAttribute::plBetCount:
            betCount = static_cast<uint32_t> (std::stoul(playerValues[attribute]));
            break;
            case PlayerAttribute::plTotalMoneyGained:
            totalMoneyGained = std::stoi(playerValues[attribute]);
            break;
            case PlayerAttribute::plTotalMoneyLost:
            totalMoneyLost = std::stoi(playerValues[attribute]);
            case PlayerAttribute::plGoodBetRatio:
            goodBetRatio = std::stod(playerValues[attribute]);
            break;
        }
    }

    Player* returnPlayer = new Player(name, totalMoneyGained, totalMoneyLost, goodBetCount, betCount, passCount, dbgLog_, goodBetRatio, playerNumber, initialBankBalance);
    return returnPlayer;    
}

std::vector<std::string> FileManager::loadFilesFromPath(const std::string path)
{
    std::vector<std::string> files;
    for(const auto& entry : std::experimental::filesystem::directory_iterator(path))
    {
        files.push_back(entry.path().string());
    }
    dbgLog_->addDebugLog(
        {dbgLog_->dbLogFManagerLoadFilesFromPath(path)}
    );

    if(!files.empty())
    {
        dbgLog_->addDebugLog(
            {dbgLog_->dbLogFManagerLoadFilesFromPathResult(path, files)}
        );
    }

    dbgLog_->buildDebugLogs();

    return files;
}

std::vector<std::string> FileManager::makeFileContentUnique(std::vector<std::string> fileContent)
{
    std::set<std::string> tmpLinesHolder;
    for(auto line : fileContent)
    {
        tmpLinesHolder.insert(line);
    }
    std::vector <std::string> uniqueContent;
    uniqueContent.assign(tmpLinesHolder.begin(), tmpLinesHolder.end());
    return uniqueContent;
}

std::string FileManager::trimPath(const std::string& rawFile)
{
    std::string plainFile = rawFile;
    plainFile.erase(plainFile.begin(), plainFile.begin() + plainFile.rfind("\\") + 1);
    plainFile.erase(plainFile.begin() + plainFile.rfind('.'), plainFile.end());
    return plainFile;
}

bool FileManager::isEntryFolder(const std::string& path)
{
    struct stat buffer;
    if( stat(path.c_str(), &buffer) == 0)
    {
        return buffer.st_mode & S_IFDIR;
    }
    
    return false;
}

void FileManager::iterateGameIdConfig(const uint16_t& nextGameId)
{
    dbgLog_->addDebugLog(
        {dbgLog_->dbLogFManagerInitConfigIterateGameId}
    );

    dbgLog_->buildDebugLogs();

    changeConfigTagValue("NextGameNumber",std::to_string(nextGameId));
}

uint16_t FileManager::nextGameSaveId()
{
    uint16_t nextId = 1;
    // Check folder for game files
    std::vector<std::string> gameSaveFolder = loadFilesFromPath(FILE_GAME_SAVE_LOG_PATH);
    std::vector<uint16_t> gameSaveIds;
    for(auto& file : gameSaveFolder)
    {
        if(isEntryFolder(file))
        {
            continue;
        }
        file = trimPath(file);
        file.erase(file.begin(), file.begin() + 6);
        gameSaveIds.push_back(std::stoi(file));
    }
    
    while(isFileGood(FILE_GAME_SAVE_LOG_PATH, "GameNr" + std::to_string(nextId) + EXT_GAME_LOG))
    {
        nextId++;
    }

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogFManagerInitConfigGetNameSaveId(nextId)}
    );
    return nextId;
}

std::string FileManager::extractConfigValueFromTag(const std::string& tag)
{
    std::vector<std::string> configTags = loadFileContent(INIT_CONFIG_PATH, INIT_CONFIG_FILE);

    for(auto configTag : configTags)
    {
        if(configTag.find(tag) != std::string::npos)
        {
            // remove whitespaces
            std::string tagValue = configTag;
            tagValue.erase(tagValue.begin(), tagValue.begin() + tagValue.rfind(":") + 1);
            return tagValue; 
        }
    }

    std::string errMsg = "No such tag found in file";
    throw std::runtime_error(errMsg);

}

void FileManager::changeConfigTagValue(const std::string& tag, const std::string& newValue)
{
    if(!isFileGood(INIT_CONFIG_PATH, INIT_CONFIG_FILE))
    {
        throw std::runtime_error("No init.cfg file found! Aborting.");
    }

    if(extractConfigValueFromTag(tag) == newValue)
    {
        std::cout << "System Message: Already the same value.\n";
    }

    std::string initPath = INIT_CONFIG_PATH;
    std::vector<std::string> oldConfigValues = loadFileContent(INIT_CONFIG_PATH, INIT_CONFIG_FILE);

    std::fstream initFile;
    initFile.open(initPath + "/" + INIT_CONFIG_FILE, std::ios::out);

    for(auto& oldConfigLine : oldConfigValues)
    {
        if(oldConfigLine.find(tag) != std::string::npos)
        {
            std::string lineTag = oldConfigLine;
            lineTag.erase(lineTag.begin() + lineTag.rfind(":") + 1, lineTag.end());
            std::string newConfigLine = lineTag += newValue;
            oldConfigLine = newConfigLine;
            break;
        }
    }

    dbgLog_->addDebugLog(
        {dbgLog_->dbLogFManagerInitConfigEditTag(tag, newValue)}
    );

    for(auto& newConfgLine : oldConfigValues)
    {
        initFile << newConfgLine << "\n";
    }

    dbgLog_->buildDebugLogs();
    
}

void FileManager::checkFiles()
{
    for(auto file : _filesToCheck)
    {
        if(!isFileGood(file.second.first, file.second.second))
        {
            touch(file.first, file.second.second);
        }
    }
}

std::vector<std::pair<double, std::string>> FileManager::loadHighscores()
 {
    // Load file content to a different container 
    std::vector<std::string> rawFileContent = loadFileContent(FILE_PLAYER_HIGHSCORES_PATH, FILE_PLAYER_HIGHSCORES);
    std::vector<std::pair<double, std::string>> finalHighscores;
    // Handle splitting values
    for(auto line : rawFileContent)
    {
        if(line == "PlaceNo,BetRatio,Name")
        {
            continue;
        }
        // Handle splitting
        std::string ratio, name;
        ratio = line; name = line;
        ratio.erase(ratio.begin(), ratio.begin() + ratio.find(',') + 1);
        ratio.erase(ratio.begin() + ratio.find(","), ratio.end());
        name.erase(name.begin(), name.begin() + name.rfind(",") + 1);


        finalHighscores.push_back(std::make_pair(std::stod(ratio), name));
    }

    std::sort(finalHighscores.begin(), finalHighscores.end());

    return finalHighscores;
 }

bool FileManager::alreadyInHighscores(const std::string& playerName, std::vector<std::pair<double, std::string>> highscores)
{
    for(auto entry : highscores)
    {
        if(playerName == entry.second)
        {
            return true;
        }
    }
    
    return false;
}

void FileManager::updateHighscores(std::vector<std::pair<double, std::string>> highscores)
{
    std::string highscoresPath = FILE_PLAYER_HIGHSCORES_PATH;
    std::ofstream highscoreFile(highscoresPath + "/" + FILE_PLAYER_HIGHSCORES);
    highscoreFile << "PlaceNo,BetRatio,Name\n";
    for(int i = 0 ; i < highscores.size(); i++)
    {
        highscoreFile << i + 1 << "," << highscores[i].first << "," << highscores[i].second << std::endl;
    }
    highscoreFile.close();
}

FileManager::FileManager(DebugLogger* dbLog)
{
    dbgLog_ = dbLog;
    dbgLog_->addDebugLog(
        {dbgLog_->dbLogClassFManagerInitialize}
    );

}
FileManager::~FileManager()
{
    dbgLog_->addDebugLog(
        {dbgLog_->dbLogClassFManageDestruct}
    );
    dbgLog_->buildDebugLogs();
}