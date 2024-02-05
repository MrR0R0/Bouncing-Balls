#pragma once
#ifndef BOUNCINGBALLS_GAME_H
#define BOUNCINGBALLS_GAME_H

#include "Menu.h"

class Game{
    public:
        void init(const char* title, int xPos, int yPos, int width, int height);
        static void handleEvents();
        static void update();
        static void render();
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
