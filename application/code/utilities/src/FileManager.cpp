#include <iostream> // For debug
#include <fstream>

#include "../include/FileManager.h"

/// @brief Checks whether or not a provided file exists
/// @param path location of file 
/// @param fileName name of the file
/// @return File state
bool FileManager::isFileGood(const std::string& path, const std::string& fileName)
{
    std::cout << path + "/" + fileName << std::endl;
    std::ifstream fileCheck(path + "/" + fileName);
    return fileCheck.good();
}


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
        createFile(FILE_GAME_SAVE_LOG, fileName);
        break;
    case GameSaveDbg:
        createFile(FILE_GAME_SAVES_LOG_DBG, fileName);
        break;
    default:
        std::cout << "No such file type in preset templates. Use createFile!\n";
        break;
    }
}

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
        switch (lineNum)
        {
        case 0:
            appendTheSave << appPlayerStat.getNickName();
            break;
        case 1:
            appendTheSave << appPlayerStat.getGlobalGoodBetCount();
            break;            
        case 2:
            appendTheSave << appPlayerStat.getGlobalBetCount();
            break;            
        case 3:
            appendTheSave << appPlayerStat.getGlobalPassCount();
            break;            
        case 4:
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