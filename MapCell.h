#pragma once
#ifndef BOUNCINGBALLS_MAPCELL_H
#define BOUNCINGBALLS_MAPCELL_H
#include "Game.h"
#include "Ball.h"

class Cell{
    public:
        double x_cent, y_cent;
        bool empty=true;
        Ball *ball;
        void render();
        void destroy();
        void moveDown(double d);
        void addBall(int);
        void dropBall();
};

#endif //BOUNCINGBALLS_MAPCELL_H
