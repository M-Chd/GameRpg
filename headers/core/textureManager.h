#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace Core {

    struct SurfaceManager
    {
        SDL_Surface* playerSurface = nullptr;
        SDL_Surface* enemySurface = nullptr;
        SDL_Surface* swordSurface = nullptr;
        SDL_Surface* bowSurface = nullptr;
        SDL_Surface* healSurface = nullptr;

        bool initSurfaces(TTF_Font* font);

    };

    struct TextureManager
    {

        SurfaceManager* surfaceManager;

        SDL_Texture* playerTexture = nullptr;
        SDL_Texture* enemyTexture = nullptr;
        SDL_Texture* swordTexture = nullptr;
        SDL_Texture* bowTexture = nullptr;
        SDL_Texture* healTexture = nullptr;
        

        void initTexture(TTF_Font* font,SDL_Renderer* renderer);
        void clear();
    };
}