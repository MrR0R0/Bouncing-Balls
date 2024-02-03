#pragma once
#ifndef BOUNCINGBALLS_FILEMANAGER_H
#define BOUNCINGBALLS_FILEMANAGER_H
#include "Utility.h"

class FileManager{
    public:
        static void addScore(const char *path, const std::string &name, unsigned int score);
        static std::vector<std::pair<unsigned int, std::string>> getTopTen(const char *path);
};





#endif //BOUNCINGBALLS_FILEMANAGER_H
