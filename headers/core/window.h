#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

namespace Core {

    struct WindowRenderer
    {
        SDL_Renderer* renderer;
        SDL_Window* window;
        TTF_Font* Titlefont;
        TTF_Font* font;
        

        bool initRenderer();
        bool initWindow(int height,int lenght);
        bool initFonts();
        void quit();
    };
}