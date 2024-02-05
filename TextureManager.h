#pragma once
#ifndef BOUNCINGBALLS_TEXTUREMANAGER_H
#define BOUNCINGBALLS_TEXTUREMANAGER_H

#include "Game.h"

class TextureManager {
public:
    static SDL_Texture *LoadTexture(const char *fileName);

    static SDL_Texture *LoadFont(const char *fileName, int size, const char *message, SDL_Color color);
};

#endif //BOUNCINGBALLS_TEXTUREMANAGER_H
