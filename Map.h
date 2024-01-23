#pragma once
#ifndef BOUNCINGBALLS_MAP_H
#define BOUNCINGBALLS_MAP_H

#include "Game.h"

class Map{
    public:
    Map();
    ~Map();

    void LoadMap(int map[18][11]);
    void DrawMap();

    private:
        SDL_Rect src, dest;
        SDL_Texture* galaxy;
        int map[20][25];
};

#endif //BOUNCINGBALLS_MAP_H
