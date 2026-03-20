#include "core/textureManager.h"

bool Core::SurfaceManager::initSurfaces(TTF_Font* font)
{
    playerSurface = IMG_Load("assets/images/Miku_forgor.png");
    if (!playerSurface) {
        std::cerr << "Failed to load player image: " << IMG_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    swordSurface = IMG_Load("assets/images/minecraft_sword.jpg");
    if (!swordSurface) {
        std::cerr << "Failed to load sword image: " << IMG_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    bowSurface = IMG_Load("assets/images/Minecraft_bow.jpg");
    if (!bowSurface) {
        std::cerr << "Failed to load bow image: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(swordSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    enemySurface = IMG_Load("assets/images/sinje.jpg");
    if (!enemySurface) {
        std::cerr << "Failed to load mob image: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(bowSurface);
        SDL_FreeSurface(swordSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    healSurface = IMG_Load("assets/images/Heal_potion.png");
    if (!healSurface) {
        std::cerr << "Failed to load heal image: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(enemySurface);
        SDL_FreeSurface(bowSurface);
        SDL_FreeSurface(swordSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return false;
    }
}

void Core::TextureManager::initTexture(TTF_Font* font,SDL_Renderer* renderer)
{
    if(!surfaceManager) return;

    playerTexture = SDL_CreateTextureFromSurface(renderer, surfaceManager->playerSurface);
    swordTexture = SDL_CreateTextureFromSurface(renderer, surfaceManager->swordSurface);
    bowTexture = SDL_CreateTextureFromSurface(renderer, surfaceManager->bowSurface);
    enemyTexture = SDL_CreateTextureFromSurface(renderer, surfaceManager->enemySurface);
    healTexture = SDL_CreateTextureFromSurface(renderer, surfaceManager->healSurface);
    SDL_FreeSurface(surfaceManager->playerSurface);
    SDL_FreeSurface(surfaceManager->swordSurface);
    SDL_FreeSurface(surfaceManager->bowSurface);
    SDL_FreeSurface(surfaceManager->enemySurface);
    SDL_FreeSurface(surfaceManager->healSurface);
}
