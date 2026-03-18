#pragma once
#include <iostream>
#include "utils/position.h"
#include "stats.h"
#include "enemy.h"
#include "inventory.h"

namespace Entities{

    class Player : public IEntity
    {
    public:
        
        Player(Utils::Position _pos, Stats _stats) : stats(_stats)
        {
            name = "Player";
            pos = _pos;
        };

        const Systems::Inventory& getInventory() { return inventory; };
        const Stats& getStats() { return stats; };
        const Utils::Position& getPos() override { return pos; }
        void setPos(Utils::Position) override;
        const std::string& getName() override { return name; };
        const EntityType getType()override{ return type; };

        void attack(std::shared_ptr<Enemy> e);
        bool isPlayerProtecting() { return isProtecting; };
        void setPlayerProtecting() { isProtecting = true; }

        void update() override;
        void render(SDL_Renderer* renderer) override;

    private:
        Stats stats;
        Systems::Inventory inventory;
        bool isProtecting;

        SDL_Texture* player_texture;
        SDL_Surface* Player_surface = nullptr;

    };
}