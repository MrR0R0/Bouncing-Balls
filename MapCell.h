#pragma once
#ifndef BOUNCINGBALLS_MAPCELL_H
#define BOUNCINGBALLS_MAPCELL_H
#include "Game.h"
#include "Ball.h"

class Cell{
    public:
        void render();
        int x_cent, y_cent, color;
        Ball *ball = new Ball;
};

#endif //BOUNCINGBALLS_MAPCELL_H
