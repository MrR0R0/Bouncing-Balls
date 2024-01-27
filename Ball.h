#pragma once
#ifndef BOUNCINGBALLS_BALL_H
#define BOUNCINGBALLS_BALL_H
#include "Game.h"

class Ball{
    public:
        void render();
        void fall();
        double x_cent, y_cent;
        int color;  // red:1 | green:2 | blue:4 | yellow:8 | purple : 16 | locked : 32
        SDL_Rect ballRect;
        SDL_Texture *ballPic;
};

#endif //BOUNCINGBALLS_BALL_H
