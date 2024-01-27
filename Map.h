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
        static std::vector<Ball*> fallingBalls;
        std::vector<Ball*> fCop;
        int initialY = -200;
        Cell *map = new Cell[120];
};

#endif //BOUNCINGBALLS_MAP_H
