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


void FileManager::createFile(const std::string& path, const std::string& filename)
{
    const std::string toMake = path + "/" + filename;
    std::ofstream makeFile;
    makeFile.open(toMake);
    if(makeFile.is_open())
    {
        std::cout << "Done!\n";
        return;
    }
    
    std::cout << "Could not create the file!\n";
}
