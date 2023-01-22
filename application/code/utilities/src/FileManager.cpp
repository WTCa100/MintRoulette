#include <iostream> // For debug
#include <fstream>
#include <experimental/filesystem>

#include "../include/FileManager.h"

/// @brief Checks whether or not a provided file exists
/// @param path location of file 
/// @param fileName name of the file
/// @return File state
bool FileManager::isFileGood(const std::string& path, const std::string& fileName)
{
    std::cout << "Debug: File: Check: Path:" << path + "/" + fileName << std::endl;
    std::ifstream fileCheck(path + "/" + fileName);
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
    switch (fType)
    {
    case PlayerStat:
        createFile(FILE_PLAYER_STATS_PATH, fileName);
        tmpPathHolder = FILE_PLAYER_STATS_PATH;
        filePath = tmpPathHolder + "/" + fileName;
        makeFile.open(filePath);
        makeFile << "Name:\nGoodBetCount:\nPassCount:\nBetCount:\nTotalMoneyGained:\n";
        makeFile.close();
        break;
    case GameSave:
        createFile(FILE_GAME_SAVE_LOG, "GameNr" + fileName + EXT_GAME_LOG);
        break;
    case GameSaveDbg:
        createFile(FILE_GAME_SAVES_LOG_DBG, fileName);
        break;
    default:
        std::cout << "No such file type in preset templates. Use createFile!\n";
        break;
    }
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
    // Get Values
    for(auto& line : playerValues)
    {
        //std::cout << "Debug: Player: Load: Attrval: " << line << std::endl;
        line.erase(line.begin(), line.begin() + line.rfind(':') + 1);
        //std::cout << "Debug: Player: Load: Attrval: Trimmed: " << line << std::endl;
    }

    // Initialize temporary values
    uint32_t goodBetCount; uint32_t passCount; uint32_t betCount; int totalMoneyGained;
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
        }
    }

    Player* returnPlayer = new Player(name, totalMoneyGained, goodBetCount, betCount, passCount, playerNumber, initialBankBalance);
    return returnPlayer;    
}

std::vector<std::string> FileManager::loadFilesFromPath(const std::string path)
{
    std::vector<std::string> files;
    for(const auto& entry : std::experimental::filesystem::directory_iterator(path))
    {
        files.push_back(entry.path().string());
    }
    return files;
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
    std::string initConfigPath = INIT_CONFIG_PATH;
    std::vector<std::string> initContent = loadFileContent(INIT_CONFIG_PATH, INIT_CONFIG_FILE);
    std::cout << "Next game Id " << nextGameId << std::endl;
    for(auto& lineContent : initContent)
    {
        if(lineContent.find("NextGameNumber") != std::string::npos)
        {
            std::cout << "Debug: Here: " << lineContent << std::endl;
            lineContent = "NextGameNumber :" + std::to_string(nextGameId);
        }
    }
    std::fstream configEdit;
    configEdit.open(initConfigPath + "/" + INIT_CONFIG_FILE);
    {  
        for(auto saveLineContent : initContent)
        {
            configEdit << saveLineContent << std::endl;
        }
    }
}