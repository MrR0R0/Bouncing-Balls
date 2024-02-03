#pragma once
#ifndef BOUNCINGBALLS_MENU_H
#define BOUNCINGBALLS_MENU_H

#include "Map.h"

enum endMenuMode{Write, Idle};

class MainMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event) const;
        SDL_Rect startRect, modeRect, scoreRect, settingRect, soundMenuRect, titleRect;
        SDL_Texture *startMessage, *modeMessage, *scoreMessage, *settingPic, *soundMenuPic, *titleMessage;
};

class ModeMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        SDL_Rect countdownRect, randomRect, infinityRect;
        SDL_Texture *countdownMessage, *randomMessage, *infinityMessage;
};

class SettingsMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event) const;
        SDL_Rect background1Rect, background2Rect, background3Rect, ball1Rect, ball2Rect, ball3Rect,
                backgroundRect, ballRect;
        SDL_Texture *theme1Pic, *theme2Pic, *theme3Pic, *ball1Pic, *ball2Pic, *ball3Pic,
                    *backgroundMessage, *ballMessage;
};

class SoundMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        static void loadMusic(const char *path);
        bool isMute;
        int prevVolume;
        SDL_Rect soundBarRect, soundMessageRect, soundRect, theme1Rect,theme2Rect, theme3Rect, musicRect, speakerRect;
        SDL_Texture *soundMessage, *theme1Message, *theme2Message, *theme3Message, *musicMessage, *speakerPic;
};

class ScoreMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        void setScores(const char* path);
        void renderScores();
        SDL_Rect scoreRect, infinityRect, countdownRect, randomRect, namesRect[10], scoresRect[10];
        SDL_Texture *scoreMessage, *infinityMessage, *countdownMessage, *randomMessage, *namesMessage[10], *scoresMessage[10];
    private:
        std::vector<std::pair<unsigned int, std::string>> scores;
};

class PlayMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        void update();
        void setAngle(int &x, int &y);
        Uint32 lastTick;
        SDL_Rect cannonRect, barRect, messageRect;
        SDL_Texture *cannonPic, *textMessage;
        Map map;
    private:
        double angle;
};

class EndMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event);
        void update();
        static std::string makeValid(const std::string &);
        int index=0;
        bool backspace=false, del=false, left=false, right=false, redirect=false;
        std::string topText;
        static std::string text, textCpy;
        SDL_Rect textRect, fullTextRect, tickRect, topRect, enterNameRect, warningRect, redirectRect;
        SDL_Texture *textMessage, *tickPic, *topMessage, *enterNameMessage, *warningMessage, *redirectMessage;
        const Uint8 *keyStates;
        endMenuMode endMode;
};
#endif //BOUNCINGBALLS_MENU_H