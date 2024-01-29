#pragma once
#ifndef BOUNCINGBALLS_MAPCELL_H
#define BOUNCINGBALLS_MAPCELL_H
#include "Game.h"
#include "Ball.h"

class Cell{
    public:
        double x_cent, y_cent, vx_cent, vy_cent;
        bool empty=true;
        Ball *ball;
        void render() const;
        void destroy();
        void addBall(int);
        void dropBall();
        void update();
};

#endif //BOUNCINGBALLS_MAPCELL_H
