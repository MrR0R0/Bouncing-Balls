#pragma once
#ifndef BOUNCINGBALLS_MAPCELL_H
#define BOUNCINGBALLS_MAPCELL_H

#include "Ball.h"

class Cell{
    public:
        double x_cent, y_cent, vx_cent, vy_cent;
        void init(double xCent, double yCent, double vxCent, double vyCent);
        void render();
        void update();
        void destroy();

        //ball related functions/variables
        void addBall(int color);
        void dropBall(int x, int y);
        void popBall(int x, int y);
        bool empty() const {return ball.empty();};
        void moveDown(int distance);
        void renderPop(std::pair<int, int> i, int popFrame);
        std::vector<Ball> ball;
};

#endif //BOUNCINGBALLS_MAPCELL_H
