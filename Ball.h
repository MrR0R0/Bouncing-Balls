#pragma once
#ifndef BOUNCINGBALLS_BALL_H
#define BOUNCINGBALLS_BALL_H

#include "Utility.h"

class Ball{
    public:
        Ball(int c, double x, double y, double vx, double vy);
        int color;  // bomb:-3 | trace:-2 | black:-1 | red:1 | green:2 | blue:4 | yellow:8 | purple : 16 | locked : 32
        static int cnst;

        void bounce();
        void render();
        void update(double acceleration);
        void moveDown(int distance);
        void renderPopFrame(int popFrame);
        void renderBurnFrame(int burnFrame);
        static void initPics();

        bool collisionWithCell(double, double);
        bool hitVerticalEdges() const;
        bool outOfScreen() const;
        bool passedTheCeiling(double ceilingHeight);

        std::pair<double, double> nextCoordinate(){return std::make_pair(x_cent + vx_cent, y_cent + vy_cent);};

        SDL_Rect ballRect;
    private:
        static SDL_Texture *lockPic, *popFrame[3], *burningFrame[3];
        double x_cent, y_cent, vx_cent, vy_cent;
        SDL_Texture *ballPic;
};

#endif //BOUNCINGBALLS_BALL_H
