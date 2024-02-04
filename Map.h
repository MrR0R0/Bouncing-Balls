#pragma once
#ifndef BOUNCINGBALLS_MAP_H
#define BOUNCINGBALLS_MAP_H

#include "MapCell.h"

class Map{
public:
    static int cellNumber;
    int initialY = -500;

    void LoadMap();
    void render();
    void update();
    void destroy();

    //cell related functions/variables
    std::vector<Cell> map;
    std::vector<int> cellColor;
    static std::set<std::pair<int, int>> nonEmptyCells;


    //ball related functions/variables
    void addShootingBall(const double &angle, SDL_Rect &cannonRect);
    bool passedTheBar(int yBar) const;
    int decideNextBallColor();
    static std::vector<Ball> fallingBalls;
    std::vector<Ball> shootingBall;
    static std::list<int> ballQueue;

private:
    //cell related functions/variables
    static bool areLoose(std::set<std::pair<int, int>> &);
    static std::vector<std::pair<int,int>> immediateNeighbors(int x, int y); //row column
    static bool inMap(int x, int y);
    void getSameColorNeighbors(int x, int y, int initialColor);
    void getNonEmptyNeighbors(int, int);
    void checkBallForFall(int x, int y);
    int closestEmptyCell(std::pair<int, int> cell, std::pair<double, double> c);
    std::set<std::pair<int, int>> nonEmptyCellsCopy;
    std::set<std::pair<int, int>> checkedBalls;
    std::set<std::pair<int, int>> vacatedCells;

    //ball related functions/variables
    std::vector<Ball> fallingBallsCopy;
    void removeInvisibleBalls();
    void dropLooseBalls();
    void updateShootingBall();
};

#endif //BOUNCINGBALLS_MAP_H