#pragma once
#ifndef BOUNCINGBALLS_BALL_H
#define BOUNCINGBALLS_BALL_H
#include "Game.h"

class Ball{
    public:
        void init(int c, double x, double y, double vx, double vy);
        bool collisionWithCell(double, double);
        bool hitVerticalEdges() const;
        bool outOfScreen() const;
        bool haveTheSameColor(int color);
        std::pair<double, double> coordinate(){return std::make_pair(x_cent, y_cent);};
        void bounce();
        void render();
        void update(double acceleration);
        void removeLock();
        int color;  // red:1 | green:2 | blue:4 | yellow:8 | purple : 16 | locked : 32
        SDL_Rect ballRect;
    private:
        static SDL_Texture *lockPic;
        static int cnst;
        double x_cent, y_cent, vx_cent, vy_cent;
        std::vector<int> decodeColor(int c);
        SDL_Texture *ballPic;
};

#endif //BOUNCINGBALLS_BALL_H
