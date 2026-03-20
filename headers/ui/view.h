#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "core/game.h"

namespace UI {

    struct View
    {

        void drawBoard(Core::Game& g) const;
        void drawInfo(Core::Game& g) const;
        void renderPlayerInfo(Core::Game& g);
        void renderText(Core::Game& g, const std::string& text,
                        int x, int y, SDL_Color c);
        void drawTitleScreen(Core::Game& g);
        void drawPauseScreen(Core::Game& g);
        void drawGameOverScreen(Core::Game& g);
        
    };
}