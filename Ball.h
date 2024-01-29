#pragma once
#ifndef BOUNCINGBALLS_BALL_H
#define BOUNCINGBALLS_BALL_H
#include "Game.h"

class Ball{
    public:
        void render();
        void update();
        double x_cent, y_cent, vx_cent, vy_cent;
        int color;  // red:1 | green:2 | blue:4 | yellow:8 | purple : 16 | locked : 32
        const int cnst = 8;
        SDL_Rect ballRect;
        SDL_Texture *ballPic;
};

#endif //BOUNCINGBALLS_BALL_H
