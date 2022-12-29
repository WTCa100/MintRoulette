#pragma once
#include <fstream>
#include <string>

class MakeBeing
{
public:
    void createFile(std::string fileName, std::string filePath) = 0;
    virtual void createDIR(std::string path) = 0;
    void deletFile(std::string fileName, std::string filePath) = 0;
};