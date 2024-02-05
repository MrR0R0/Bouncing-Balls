#include "Game.h"

using namespace std;

Game game;

int main(int argc, char *argv[]) {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    Uint32 frameTime;

    game.init("Hi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800);

    while (Game::isRunning) {
        frameStart = SDL_GetTicks();
        Game::handleEvents();
        Game::update();
        game.render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
    game.clean();
    return 0;
}