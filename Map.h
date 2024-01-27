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
        Cell *map = new Cell[400];

};

#endif //BOUNCINGBALLS_MAP_H
