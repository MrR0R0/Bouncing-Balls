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
        std::vector<std::pair<int,int>> immediateNeighbors(int x, int y); //row column
        void dropLooseBalls();
        bool inMap(int x, int y);
        static std::vector<Ball*> fallingBalls;
        int initialY = 0;
        Cell *map;
    private:
        std::set<std::pair<int, int>> sameColorNeighbors;
        std::set<std::pair<int, int>> checkedBalls;
        std::set<std::pair<int, int>> nonEmptyNeighbors;
        std::vector<Ball*> fallingBallsCopy;
        double speed=1, acceleration=2;
};

#endif //BOUNCINGBALLS_MAP_H
