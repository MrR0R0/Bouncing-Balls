#pragma once
#ifndef BOUNCINGBALLS_GAME_H
#define BOUNCINGBALLS_GAME_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <time.h>

void setRectWithCenter(SDL_Rect &rect, double x, double y, double w, double h);
void setRectWithCorner(SDL_Rect &rect, double x, double y, double w, double h);
bool pointInRect(SDL_Rect rect, int &x, int &y);

enum menuModes{Main, Modes, Settings, Sound, Score, Play, End};
enum gameModes{Infinity, Random, Countdown};
enum ballThemes{Bowling, Glass, Marble};

class Game{
    public:
        void init(const char* title, int xPos, int yPos, int width, int height);
        static void handleEvents();
        static void update();
        void render();
        void clean();
        static SDL_Texture *background;
        static SDL_Renderer *renderer;
        static bool isRunning;
        static gameModes gameMode;
        static SDL_Rect backgroundRect;
        static Mix_Music *music;
        static menuModes lastMenu();
        static ballThemes ballTheme;
        static std::vector<menuModes> menuQueue;
        static unsigned int score;

    private:
        SDL_Window* window;
};

#endif //BOUNCINGBALLS_GAME_H
