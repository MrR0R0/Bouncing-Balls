#include "FileManager.h"

void FileManager::addScore(const char *path, const std::string &name, unsigned int score) {
    std::ofstream f(path, std::ios::app);
    f << score << " " << name << "\n";
    f.close();
}

std::vector<std::pair<unsigned int, std::string>> FileManager::getTopTen(const char *path) {
    std::vector<std::pair<unsigned int, std::string>> topTen;
    std::string name, line, temp;
    long long score;
    std::ifstream f(path, std::ios::in);
    while (std::getline(f, line)){
        std::istringstream iss(line);
        std::size_t found = line.find(' ');
        iss >> score;
        name = line.substr(found+1, line.length()-found);
        topTen.push_back(std::make_pair(score, name));
    }
    f.close();
    sort(topTen.rbegin(), topTen.rend());
    return topTen;
}