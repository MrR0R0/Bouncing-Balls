#include "Game.h"

using namespace std;

Game game;

int main(int argc, char* argv[]) {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game.init("Hi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800);

    while(game.isRunning){
        frameStart = SDL_GetTicks();
        game.handleEvents();
        game.update();
        game.render();
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
    game.clean();
    return 0;
}
