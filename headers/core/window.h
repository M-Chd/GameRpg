#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace Core {

    struct WindowRenderer
    {
        SDL_Renderer* renderer = nullptr;
        SDL_Window* window = nullptr;
        TTF_Font* Titlefont = nullptr;
        TTF_Font* font = nullptr;
        

        bool initRenderer();
        bool initWindow(int height,int lenght);
        bool initFonts();
        void quit();
    };
}