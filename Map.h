#pragma once
#ifndef BOUNCINGBALLS_MAP_H
#define BOUNCINGBALLS_MAP_H

#include "Game.h"
#include "MapCell.h"

class Map{
    public:
        void LoadMap();
        void render();
        void update();
        void destroy();
        void getSameColorNeighbors(int x, int y);
        void getNonEmptyNeighbors(int, int);
        void removeInvisibleBalls();
        void addShootingBall(const double &angle, SDL_Rect &cannonRect);
        void updateShootingBalls();
        void checkBallForFall(int x, int y);
        bool passedTheBar(int yBar) const;
        std::pair<int, int> closestEmptyCell(std::pair<int, int> cell, std::pair<double, double> c) const;
        static std::vector<std::pair<int,int>> immediateNeighbors(int x, int y); //row column
        void dropLooseBalls();
        static bool inMap(int x, int y);
        static bool inScreen(double &y);
        static std::vector<Ball*> fallingBalls;
        static std::set<std::pair<int, int>> nonEmptyCells;
        static std::set<std::pair<int, int>> sameColorNeighbors;
        static int cellNumber;
        int initialY = -100;
        Cell *map;
    private:
        std::set<std::pair<int, int>> nonEmptyNeighbors;
        std::set<std::pair<int, int>> nonEmptyCellsCopy;
        std::set<std::pair<int, int>> newFilledCells;
        std::set<std::pair<int, int>> checkedBalls;
        std::vector<Ball*> fallingBallsCopy;
        std::set<Ball*> shootingBalls;
        std::set<Ball*> stationaryBalls;
        std::set<Ball*> shootingBallsCopy;
};

#endif //BOUNCINGBALLS_MAP_H
