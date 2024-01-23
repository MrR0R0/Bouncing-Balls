#pragma once
#ifndef BOUNCINGBALLS_MENU_H
#define BOUNCINGBALLS_MENU_H
#include "Game.h"

void setRectWithCenter(SDL_Rect &rect, int x, int y, int w, int h);
bool pointInRect(SDL_Rect rect, int x, int y);

class MainMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        SDL_Rect startRect, modeRect, scoreRect, settingRect, audioRect, titleRect;
        SDL_Texture *startMessage, *modeMessage, *scoreMessage, *settingPic, *audioPic, *titleMessage;
};

class ModeMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        SDL_Rect countdownRect, randomRect, infinityRect, backRect;
        SDL_Texture *countdownMessage, *randomMessage, *infinityPic, *backPic;
};

class SettingsMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        SDL_Rect theme1Rect, theme2Rect, theme3Rect, ball1Rect, ball2Rect, ball3Rect,
                backgroundRect, ballRect, backRect;
        SDL_Texture *theme1Pic, *theme2Pic, *theme3Pic, *ball1Pic, *ball2Pic, *ball3Pic,
                    *backgroundMessage, *ballMessage, *backPic;
};

class SoundMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        void loadMusic(const char *path);
        SDL_Rect soundBarRect, soundMessageRect, soundRect, theme1Rect, theme2Rect, theme3Rect, musicRect, backRect;
        SDL_Texture *soundMessage, *theme1Message, *theme2Message, *theme3Message, *musicMessage, *backPic;
};

class ScoreMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        SDL_Rect scoreRect, infinityRect, countdownRect, randomRect, backRect;
        SDL_Texture *scoreMessage, *infinityMessage, *countdownMessage, *randomMessage, *backPic;
};
#endif //BOUNCINGBALLS_MENU_H
