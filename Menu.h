#pragma once
#ifndef BOUNCINGBALLS_MENU_H
#define BOUNCINGBALLS_MENU_H

#include "Map.h"
#include "TextureManager.h"
#include "Paths.h"

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
                backgroundMessageRect, ballMessageRect;
        SDL_Texture *background1Pic, *background2Pic, *background3Pic, *ball1Pic, *ball2Pic, *ball3Pic,
                    *backgroundMessage, *ballMessage;
};

class SoundMenu{
    public:
        void init();
        void render();
        void handleEvents(SDL_Event event);
        static void loadMusic(const char *path);
        static bool isMute;
        static int prevVolume;
        static SDL_Rect soundBarRect, soundRect;
        static SDL_Texture *speakerPic;
        SDL_Rect volumeMessageRect, theme1Rect, theme2Rect, theme3Rect, musicRect, speakerRect;
        SDL_Texture *volumeMessage, *theme1Message, *theme2Message, *theme3Message, *musicMessage;
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
        static void init();
        void render();
        void handleEvents(SDL_Event event);
        void update();
        void setAngle(int &x, int &y);
        static Uint32 lastTick;
        static SDL_Rect cannonRect, barRect, messageRect, pauseMenuRect;
        static SDL_Texture *cannonPic, *textMessage, *pauseMenuPic;
        static Map map;
        const Uint8 *keyStates;
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

class PauseMenu{
public:
    void init();
    void render();
    void handleEvents(SDL_Event event);
    static SDL_Rect soundRect, soundBarRect;
    static SDL_Texture *speakerPic;
    SDL_Rect background1Rect, background2Rect, background3Rect,
            pauseMessageRect, backgroundMessageRect;
    SDL_Texture *background1Pic, *background2Pic, *background3Pic,
            *pauseMessage, *backgroundMessage;

    SDL_Rect theme1Rect,theme2Rect, theme3Rect, musicRect, speakerRect;
    SDL_Texture *theme1Message, *theme2Message, *theme3Message, *musicMessage;
};



#endif //BOUNCINGBALLS_MENU_H