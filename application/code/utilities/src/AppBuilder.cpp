#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <windows.h>

#include "../include/AppBuilder.h"
#include "../include/Paths.h"


void AppBuilder::createDirectory(const std::string& pathToSet)
{
    const std::string sysCommandExec = "mkdir " + pathToSet;
    do
    {
        std::cout << sysCommandExec << std::endl;
        system(sysCommandExec.c_str());
    }while(!isDirectoryGood(pathToSet));
    std::cout << "Done!\n";
}

bool AppBuilder::isDirectoryGood(const std::string& path)
{
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

void AppBuilder::checkDirectories()
{
    if(_pathsToCheck.empty())
    {
        std::cout << "Nothing to check!\n";
        return;
    }

    for(auto path: _pathsToCheck)
    {
        std::cout << "Checking " << path << " ...\n";
        if(!isDirectoryGood(path))
        {
            std::cout << "Not found!\n";
            std::cout << "Attempting to create " << path << std::endl;
            createDirectory(path);
            continue;
        }

        std::cout << "Found!\n";

    }
}