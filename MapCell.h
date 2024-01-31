#pragma once
#ifndef BOUNCINGBALLS_MAPCELL_H
#define BOUNCINGBALLS_MAPCELL_H
#include "Game.h"
#include "Ball.h"

class Cell{
    public:
        void init(double xCent, double yCent, double vxCent, double vyCent);
        double x_cent, y_cent, vx_cent, vy_cent;
        bool empty = true;
        Ball *ball = nullptr;
        void render() const;
        void destroy();
        void addBall(int color);
        void dropBall(int x, int y);
        void update();
};

#endif //BOUNCINGBALLS_MAPCELL_H
