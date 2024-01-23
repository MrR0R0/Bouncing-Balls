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
SDL_Rect destR;

SDL_Renderer *Game::renderer = nullptr;
SDL_Texture *Game::background = nullptr;
menuModes Game::menuMode = Score;
bool Game::isRunning = true;
std::string Game::gameMode = "random";
Mix_Music *Game::music = Mix_LoadMUS("..\\assets\\ice_dance.mp3");

Game::Game(){}

Game::~Game(){}

void Game::init(const char* title, int xpos, int ypos, int width, int height){
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        cout << "Subsys initialized" << endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
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
    background = TextureManager::LoadTexture(theme1Path);
    TTF_Init();
    mainMenu.init();
    modesMenu.init();
    settingsMenu.init();
    soundMenu.init();
    scoreMenu.init();
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(menuMode){
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
    }
}

void Game::update(){

}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, nullptr, &backgroundRect);
    switch(menuMode){
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
    }
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game Cleaned!" << endl;
}