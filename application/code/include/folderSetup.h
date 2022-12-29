#pragma once
#include <string>
#include <fstream>
#include <sys/stat.h>

#include "fileManager.h"

class MakePath : public MakeBeing
{
    void createDIR(std::string path) override;
};