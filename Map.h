#pragma once
#ifndef BOUNCINGBALLS_MAP_H
#define BOUNCINGBALLS_MAP_H

#include "Game.h"
#include "MapCell.h"

class Map{
    public:
        void LoadMap();
        void render() const;
        void update();
        void destroy();
        void getSameColorNeighbors(int x, int y);
        void getNonEmptyNeighbors(int, int);
        void removeInvisibleBalls();
        void addShootingBall(const double &angle, SDL_Rect &cannonRect);
        static std::vector<std::pair<int,int>> immediateNeighbors(int x, int y); //row column
        void dropLooseBalls();
        static bool inMap(int x, int y);
        static std::vector<Ball*> fallingBalls;
        int initialY = 0;
        Cell *map;
    private:
        std::set<std::pair<int, int>> sameColorNeighbors;
        std::set<std::pair<int, int>> checkedBalls;
        std::set<std::pair<int, int>> nonEmptyNeighbors;
        std::vector<Ball*> fallingBallsCopy;
        std::vector<Ball*> shootingBalls;
        std::vector<Ball*> shootingBallsCopy;
        double acceleration=2;
};

#endif //BOUNCINGBALLS_MAP_H
