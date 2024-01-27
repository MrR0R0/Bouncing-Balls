#pragma once
#ifndef BOUNCINGBALLS_MENU_H
#define BOUNCINGBALLS_MENU_H
#include "Game.h"
#include "Map.h"

enum endMenuMode{Write, Idle};

class MainMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        SDL_Rect startRect, modeRect, scoreRect, settingRect, soundMenuRect, titleRect;
        SDL_Texture *startMessage, *modeMessage, *scoreMessage, *settingPic, *soundMenuPic, *titleMessage;
};

class ModeMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        SDL_Rect countdownRect, randomRect, infinityRect, backRect;
        SDL_Texture *countdownMessage, *randomMessage, *infinityMessage, *backPic;
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
        static void loadMusic(const char *path);
        bool isMute;
        int prevVolume;
        SDL_Rect soundBarRect, soundMessageRect, soundRect, theme1Rect,theme2Rect, theme3Rect, musicRect, backRect, speakerRect;
        SDL_Texture *soundMessage, *theme1Message, *theme2Message, *theme3Message, *musicMessage, *backPic, *speakerPic;
};

class ScoreMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        void setScores(const char* path);
        void renderScores();
        SDL_Rect scoreRect, infinityRect, countdownRect, randomRect, backRect, namesRect[10], scoresRect[10];
        SDL_Texture *scoreMessage, *infinityMessage, *countdownMessage, *randomMessage, *backPic, *namesMessage[10], *scoresMessage[10];
    private:
        std::vector<std::pair<unsigned int, std::string>> scores;
};

class PlayMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        void update();
        SDL_Rect backRect;
        SDL_Texture *backPic = nullptr;
        Map mp;
};

class EndMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event);
        void update();
        std::string makeValid(const std::string);
        int index=0;
        bool backspace=false, del=false, left=false, right=false, redirect=false;
        std::string topText;
        static std::string text, textCpy;
        SDL_Rect textRect, fullTextRect, tickRect, topRect, enterNameRect, warningRect, redirectRect;
        SDL_Texture *textMessage, *tickPic, *topMessage, *enterNameMessage, *warningMessage, *redirectMessage;
        const Uint8 *keystates;
        endMenuMode endMode;

};
#endif //BOUNCINGBALLS_MENU_H