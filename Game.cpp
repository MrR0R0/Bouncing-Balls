#include "Game.h"
#include "Menu.h"
#include "Paths.h"
#include "TextureManager.h"

using namespace std;

MainMenu mainMenu;
ModeMenu modesMenu;
SettingsMenu settingsMenu;
SoundMenu soundMenu;
ScoreMenu scoreMenu;
PlayMenu playMenu;
EndMenu endMenu;
PauseMenu pauseMenu;

SDL_Renderer *Game::renderer = nullptr;
SDL_Texture *Game::background = nullptr;
SDL_Rect Game::backgroundRect;
bool Game::isRunning = true;
unsigned int Game::score=0;
gameModes Game::gameMode = Random;
ballThemes Game::ballTheme = Glass;
Mix_Music *Game::music = Mix_LoadMUS("..\\assets\\ice_dance.mp3");
vector<menuModes> Game::menuQueue;

void Game::init(const char* title, int xPos, int yPos, int width, int height){
    menuQueue.push_back(Main);
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        cout << "Subsystem initialized" << endl;
        window = SDL_CreateWindow(title, xPos, yPos, width, height, 0);
        if(window){
            cout << "window created!" << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            cout << "renderer created!" << endl;
        }
        isRunning = true;
    }
    else {
        isRunning = false;
    }
    backgroundRect.w = 600;
    backgroundRect.h = 800;
    background = TextureManager::LoadTexture(background1Path);
    TTF_Init();
    SDL_StartTextInput();
    mainMenu.init();
    modesMenu.init();
    settingsMenu.init();
    soundMenu.init();
    playMenu.init();
    scoreMenu.init();
    endMenu.init();
    pauseMenu.init();
}

menuModes Game::lastMenu() {
    if(!menuQueue.empty()){
        return menuQueue.back();
    }
    return Main;
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(lastMenu()){
        case Main:
            mainMenu.handleEvents(event);
            break;
        case Modes:
            modesMenu.handleEvents(event);
            break;
        case Settings:
            settingsMenu.handleEvents(event);
            break;
        case Sound:
            soundMenu.handleEvents(event);
            break;
        case Score:
            scoreMenu.handleEvents(event);
            break;
        case Play:
            playMenu.handleEvents(event);
            break;
        case End:
            endMenu.handleEvents(event);
            break;
        case Pause:
            pauseMenu.handleEvents(event);
            break;
    }
}

void Game::update(){
    switch(lastMenu()){
        case Play:
            playMenu.update();
            break;
        case End:
            endMenu.update();
            break;
        default:
            break;
    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, nullptr, &backgroundRect);
    switch(lastMenu()){
        case Main:
            mainMenu.render();
            break;
        case Modes:
            modesMenu.render();
            break;
        case Settings:
            settingsMenu.render();
            break;
        case Sound:
            soundMenu.render();
            break;
        case Score:
            scoreMenu.render();
            break;
        case Play:
            playMenu.render();
            break;
        case End:
            endMenu.render();
            break;
        case Pause:
            pauseMenu.render();
            break;
    }
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_StopTextInput();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
    cout << "Game Cleaned!" << endl;
}