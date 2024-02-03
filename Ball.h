#pragma once
#ifndef BOUNCINGBALLS_BALL_H
#define BOUNCINGBALLS_BALL_H

#include "Utility.h"

class Ball{
    public:
        Ball(int c, double x, double y, double vx, double vy);
        int color;  // red:1 | green:2 | blue:4 | yellow:8 | purple : 16 | locked : 32
        static int cnst;

        void bounce();
        void render();
        void update(double acceleration);

        bool collisionWithCell(double, double);
        bool hitVerticalEdges() const;
        bool outOfScreen() const;
        bool haveTheSameColor(int color);

        std::pair<double, double> coordinate(){return std::make_pair(x_cent, y_cent);};
    private:
        SDL_Rect ballRect;
        static SDL_Texture *lockPic;
        double x_cent, y_cent, vx_cent, vy_cent;
        SDL_Texture *ballPic;
};

#endif //BOUNCINGBALLS_BALL_H
