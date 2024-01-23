#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {

    SDL_Surface* tmpSurface = IMG_Load(fileName);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return tex;
}

SDL_Texture *TextureManager::LoadFont(const char* fileName, int size, const char* message, SDL_Color color){
    TTF_Font *font = TTF_OpenFont(fileName, size);
    SDL_Surface *tmpSurface = TTF_RenderText_Solid(font, message, color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return tex;
}