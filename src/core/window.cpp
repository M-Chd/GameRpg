#include "core/window.h"

bool Core::WindowRenderer::initRenderer()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;

    renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

bool Core::WindowRenderer::initWindow(int height, int length)
{
    window = SDL_CreateWindow("Game RPG v1.1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        height,
        length,
        0);

    if (!window)
    {
        SDL_Quit();
        return false;
    }
}

bool Core::WindowRenderer::initFonts()
{
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    font = TTF_OpenFont("assets/fonts/IMPACT.ttf", 20);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    Titlefont = TTF_OpenFont("assets/fonts/Beach-Ball.ttf",30);
    if (!Titlefont) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return false;
    }
}

void Core::WindowRenderer::quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_CloseFont(Titlefont);
    TTF_Quit();
    SDL_Quit();

    /*DEBUG CONSOLE*/
    std::cout<<"+ Game closed..."<<"\n";
}