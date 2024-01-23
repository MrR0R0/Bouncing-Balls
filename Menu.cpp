#include "Menu.h"
#include "TextureManager.h"
#include "Paths.h"

SDL_Color white = {255, 255, 255};
SDL_Color cyan = {127,255,212};

void setRectWithCenter(SDL_Rect &rect, int x, int y, int w, int h) {
    rect.x = x - w/2;
    rect.y = y - h/2;
    rect.w = w;
    rect.h = h;
}

bool pointInRect(SDL_Rect rect, int x, int y) {
    if((x >= rect.x && x <= rect.x+rect.w) && (y >= rect.y && y <= rect.y+rect.h))
        return true;
    return false;
}

void MainMenu::init(){
    setRectWithCenter(titleRect, 300, 100, 300, 80);
    setRectWithCenter(startRect, 300, 250, 100, 50);
    setRectWithCenter(modeRect, 300, 400, 100, 50);
    setRectWithCenter(scoreRect, 300, 550, 180, 50);
    setRectWithCenter(audioRect, 500, 700, 64, 64);
    setRectWithCenter(settingRect, 100, 700, 64, 64);
    titleMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 30, "Bouncing Balls", cyan);
    startMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Start!", white);
    modeMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Modes", white);
    scoreMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Score Board", white);
    audioPic = TextureManager::LoadTexture("..\\assets\\speaker.jpg");
    settingPic = TextureManager::LoadTexture("..\\assets\\cog.png");
}

void MainMenu::render(){
    SDL_RenderCopy(Game::renderer, titleMessage, nullptr, &titleRect);
    SDL_RenderCopy(Game::renderer, startMessage, nullptr, &startRect);
    SDL_RenderCopy(Game::renderer, modeMessage, nullptr, &modeRect);
    SDL_RenderCopy(Game::renderer, scoreMessage, nullptr, &scoreRect);
    SDL_RenderCopy(Game::renderer, audioPic, nullptr, &audioRect);
    SDL_RenderCopy(Game::renderer, settingPic, nullptr, &settingRect);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &startRect);
    SDL_RenderDrawRect(Game::renderer, &modeRect);
    SDL_RenderDrawRect(Game::renderer, &scoreRect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void MainMenu::handleEvents(SDL_Event event) {
    int x_mouse, y_mouse;
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(scoreRect, x_mouse, y_mouse))
                Game::menuMode = Score;
            else if(pointInRect(startRect, x_mouse, y_mouse))
                Game::menuMode = Start;
            else if(pointInRect(modeRect, x_mouse, y_mouse))
                Game::menuMode = Modes;
            else if(pointInRect(settingRect, x_mouse, y_mouse))
                Game::menuMode = Settings;
            else if(pointInRect(audioRect, x_mouse, y_mouse))
                Game::menuMode = Sound;
            break;
        default:
            break;
    }
}

void ModeMenu::init(){
    setRectWithCenter(countdownRect, 300, 250, 150, 50);
    setRectWithCenter(randomRect, 300, 350, 100, 50);
    setRectWithCenter(infinityRect, 300, 450, 100, 50);
    setRectWithCenter(backRect, 100, 100, 64, 64);
    countdownMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Countdown", white);
    randomMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Random", white);
    infinityPic = TextureManager::LoadTexture("..\\assets\\infinity_sign.png");
    backPic = TextureManager::LoadTexture(backPicPath);
}

void ModeMenu::render(){
    SDL_RenderCopy(Game::renderer, countdownMessage, nullptr, &countdownRect);
    SDL_RenderCopy(Game::renderer, randomMessage, nullptr, &randomRect);
    SDL_RenderCopy(Game::renderer, infinityPic, nullptr, &infinityRect);
    SDL_RenderCopy(Game::renderer, backPic, nullptr, &backRect);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &infinityRect);
    SDL_RenderDrawRect(Game::renderer, &randomRect);
    SDL_RenderDrawRect(Game::renderer, &countdownRect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void ModeMenu::handleEvents(SDL_Event event) {
    int x_mouse, y_mouse;
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(backRect, x_mouse, y_mouse))
                Game::menuMode = Main;
            else if(pointInRect(countdownRect, x_mouse, y_mouse)) {
                Game::gameMode = "countdown";
            }
            else if(pointInRect(infinityRect, x_mouse, y_mouse)) {
                Game::gameMode = "infinity";
            }
            else if(pointInRect(randomRect, x_mouse, y_mouse)) {
                Game::gameMode = "random";
            }
            break;
        default:
            break;
    }
}

void SettingsMenu::init(){
    setRectWithCenter(theme1Rect, 112, 300, 150, 300);
    setRectWithCenter(theme2Rect, 300, 300, 150, 300);
    setRectWithCenter(theme3Rect, 487, 300, 150, 300);
    setRectWithCenter(ball1Rect, 150, 600, 50, 50);
    setRectWithCenter(ball2Rect, 300, 600, 50, 50);
    setRectWithCenter(ball3Rect, 450, 600, 50, 50);
    setRectWithCenter(backgroundRect, 300, 100, 150, 50);
    setRectWithCenter(ballRect, 300, 525, 150, 50);
    setRectWithCenter(backRect, 75, 75, 64, 64);
    backgroundMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Backgrounds", white);
    ballMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Ball Texture", white);
    theme1Pic = TextureManager::LoadTexture(theme1Path);
    theme2Pic = TextureManager::LoadTexture(theme2Path);
    theme3Pic = TextureManager::LoadTexture(theme3Path);
    ball1Pic = TextureManager::LoadTexture(ball1Path);
    ball2Pic = TextureManager::LoadTexture(ball2Path);
    ball3Pic = TextureManager::LoadTexture(ball3Path);
    backPic = TextureManager::LoadTexture(backPicPath);
}

void SettingsMenu::render(){
    SDL_RenderCopy(Game::renderer, backgroundMessage, nullptr, &backgroundRect);
    SDL_RenderCopy(Game::renderer, ballMessage, nullptr, &ballRect);
    SDL_RenderCopy(Game::renderer, theme1Pic, nullptr, &theme1Rect);
    SDL_RenderCopy(Game::renderer, theme2Pic, nullptr, &theme2Rect);
    SDL_RenderCopy(Game::renderer, theme3Pic, nullptr, &theme3Rect);
    SDL_RenderCopy(Game::renderer, ball1Pic, nullptr, &ball1Rect);
    SDL_RenderCopy(Game::renderer, ball2Pic, nullptr, &ball2Rect);
    SDL_RenderCopy(Game::renderer, ball3Pic, nullptr, &ball3Rect);
    SDL_RenderCopy(Game::renderer, backPic, nullptr, &backRect);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &theme1Rect);
    SDL_RenderDrawRect(Game::renderer, &theme2Rect);
    SDL_RenderDrawRect(Game::renderer, &theme3Rect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void SettingsMenu::handleEvents(SDL_Event event){
    int x_mouse, y_mouse;
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(backRect, x_mouse, y_mouse)) {
                Game::menuMode = Main;
            }
            else if(pointInRect(theme1Rect, x_mouse, y_mouse)) {
                Game::background = TextureManager::LoadTexture(theme1Path);
            }
            else if(pointInRect(theme2Rect, x_mouse, y_mouse)) {
                Game::background = TextureManager::LoadTexture(theme2Path);
            }
            else if(pointInRect(theme3Rect, x_mouse, y_mouse)) {
                Game::background = TextureManager::LoadTexture(theme3Path);
            }
            break;
        default:
            break;
    }
}

void SoundMenu::init() {
    setRectWithCenter(theme1Rect, 100, 600, 50, 50);
    setRectWithCenter(theme2Rect, 300, 600, 50, 50);
    setRectWithCenter(theme3Rect, 500, 600, 50, 50);
    setRectWithCenter(musicRect, 300, 450, 50, 50);
    setRectWithCenter(soundBarRect, 300, 300, 200, 50);
    setRectWithCenter(soundRect,  300, 300, 200, 50);
    setRectWithCenter(soundMessageRect, 300, 200, 200, 50);
    setRectWithCenter(backRect, 50, 50, 50, 50);
    soundMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Sound", white);
    musicMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Music", white);
    theme1Message = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Mario", white);
    theme2Message = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "...", white);
    theme3Message = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "...", white);
    backPic = TextureManager::LoadTexture(backPicPath);
    loadMusic("..\\assets\\ice_dance.mp3");
}

void SoundMenu::render(){
    SDL_RenderCopy(Game::renderer, musicMessage, nullptr, &musicRect);
    SDL_RenderCopy(Game::renderer, theme1Message, nullptr, &theme1Rect);
    SDL_RenderCopy(Game::renderer, theme2Message, nullptr, &theme2Rect);
    SDL_RenderCopy(Game::renderer, theme3Message, nullptr, &theme3Rect);
    SDL_RenderCopy(Game::renderer, soundMessage, nullptr, &soundMessageRect);
    SDL_RenderCopy(Game::renderer, backPic, nullptr, &backRect);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &theme1Rect);
    SDL_RenderDrawRect(Game::renderer, &theme2Rect);
    SDL_RenderDrawRect(Game::renderer, &theme3Rect);
    SDL_RenderDrawRect(Game::renderer, &soundRect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(Game::renderer, &soundBarRect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void SoundMenu::handleEvents(SDL_Event event){
    int x_mouse, y_mouse;
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(soundRect, x_mouse, y_mouse)) {
                soundBarRect.w = x_mouse - soundRect.x;
                Mix_VolumeMusic((int)(x_mouse - soundRect.x)*128.0/soundRect.w);
            }
            else if(pointInRect(backRect, x_mouse, y_mouse)){
                Game::menuMode = Main;
            }
            else if(pointInRect(theme1Rect, x_mouse, y_mouse)) {
                loadMusic(music1Path);
            }
            else if(pointInRect(theme2Rect, x_mouse, y_mouse)) {
                loadMusic(music2Path);
            }
            else if(pointInRect(theme3Rect, x_mouse, y_mouse)) {
                loadMusic(music3Path);
            }
            break;
        default:
            break;
    }
}

void SoundMenu::loadMusic(const char *path) {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048);
    Game::music = Mix_LoadMUS(path);
    if(Game::music == nullptr)
        std::cout << "Failed to load the music!\n";
    Mix_PlayMusic(Game::music, -1);
}

void ScoreMenu::init(){
    setRectWithCenter(scoreRect, 300, 100, 250, 70);
    setRectWithCenter(infinityRect, 120, 200, 100, 50);
    setRectWithCenter(countdownRect, 300, 200, 150, 50);
    setRectWithCenter(randomRect, 480, 200, 100, 50);
    setRectWithCenter(backRect, 50, 50, 50, 50);
    infinityMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "infinity", white);
    randomMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "random", white);
    scoreMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 28, "Highest Scores", white);
    countdownMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "countdown", white);
    backPic = TextureManager::LoadTexture(backPicPath);
}

void ScoreMenu::render(){
    SDL_RenderCopy(Game::renderer, infinityMessage, nullptr, &infinityRect);
    SDL_RenderCopy(Game::renderer, countdownMessage, nullptr, &countdownRect);
    SDL_RenderCopy(Game::renderer, randomMessage, nullptr, &randomRect);
    SDL_RenderCopy(Game::renderer, scoreMessage, nullptr, &scoreRect);
    SDL_RenderCopy(Game::renderer, backPic, nullptr, &backRect);
}

void ScoreMenu::handleEvents(SDL_Event event){
    int x_mouse, y_mouse;
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(backRect, x_mouse, y_mouse)){
                Game::menuMode = Main;
            }
            break;
        default:
            break;
    }
}