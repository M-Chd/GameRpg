#pragma once
#include <SDL2/SDL.h>
#include "core/game.h"
#include "entities/enemy.h"
#include "turn.h"

static SDL_Color white = {255, 255, 255, 255};
static SDL_Color green = {15,255,0,0};
static SDL_Color red = {155,0,0,0};
static SDL_Color yellow = {255, 255, 0, 255};

namespace Entities
{
    class Enemy;
    class Player;
}

namespace Systems {

    void handlePlayerTurn(Core::Game& game,Turn& turn, std::shared_ptr<Entities::Enemy> mob,
                      int& selectedIndex, bool& inventorySelected,
                      bool& isCombatOver);

    void handleMobTurn(Core::Game& game, std::shared_ptr<Entities::Enemy> mob);
    void StartFight(Core::Game& game,
                std::shared_ptr<Entities::Enemy> e);

}