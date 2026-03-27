#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "core/game.h"
#include "systems/turn.h"

namespace UI {

    struct View
    {

        void drawBoard(const Core::Game& g) const;
        void drawInfo(const Core::Game& g) const;
        void renderPlayerInfo(Core::Game& g);
        void renderText(const Core::Game& g, const std::string& text,
                        int x, int y, SDL_Color c);
        void drawTitleScreen(const Core::Game& g);
        void drawPauseScreen(const Core::Game& g);
        void drawGameOverScreen(const Core::Game& g);
        void draw(Core::Game& g);
        void getItemInventory(Core::Game& g);

        void drawCombat(Core::Game& g,
                std::shared_ptr<Entities::Enemy> mob,
                Systems::Turn currentTurn,
                int selectedIndex,
                bool isInventorySelected);
        
    private:
        void drawCombatSprites(Core::Game& g, std::shared_ptr<Entities::Enemy> mob);
        void drawCombatHUD(Core::Game& g, std::shared_ptr<Entities::Enemy> mob);
        void drawCombatMenu(Core::Game& g, int selectedIndex);
        void drawCombatTurn(Core::Game& g, std::shared_ptr<Entities::Enemy> mob, Systems::Turn turn);
    };
}