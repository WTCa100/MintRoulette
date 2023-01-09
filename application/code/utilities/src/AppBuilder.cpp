#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <windows.h>

#include "../include/AppBuilder.h"
#include "../include/Paths.h"

void AppBuilder::createDirectory(const std::pair<std::string, std::string>& setupPath)
{
    do
    {
        system(setupPath.second.c_str());
    }while(!isDirectoryGood(setupPath.first));
}

bool AppBuilder::isDirectoryGood(const std::string& path)
{
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

void AppBuilder::checkDirectories()
{
    for(auto path : _pathCheckingMap)
    {
        std::cout << "Checking " << path.first << std::endl;
        if(isDirectoryGood(path.first))
        {
            std::cout << "Found!\n";
            continue;
        }
        std::cout << "Not found!\n";

        {
        std::cout << "Creating " << path.first << std::endl;
        createDirectory(path);
        }

        std::cout << "Continuing...\n";
    }
}
