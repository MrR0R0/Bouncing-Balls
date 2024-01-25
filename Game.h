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

enum menuModes{Main, Modes, Settings, Sound, Score, Start};

class Game{
    public:
        Game();
        ~Game();
        void init(const char* title, int xpos, int ypos, int width, int height);
        void handleEvents();
        void update();
        void render();
        void clean();
        static SDL_Texture *background;
        static SDL_Renderer *renderer;
        //static std::string mode;
        static menuModes menuMode;
        static bool isRunning;
        static std::string gameMode;
        static Mix_Music *music;

    private:
        SDL_Window* window;
        SDL_Rect backgroundRect;
};

#endif //BOUNCINGBALLS_GAME_H
