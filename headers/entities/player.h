#pragma once
#include <iostream>
#include "utils/position.h"
#include "core/board.h"
#include "stats.h"
#include "enemy.h"
#include "systems/inventory.h"
#include "utils/direction.h"
#include "core/game.h"
#include "systems/combat.h"

namespace Core
{
    class Board;
}

namespace Entities{

    class Player : public IEntity, public std::enable_shared_from_this<Player>
    {
    public:
        
        Player(Utils::Position _pos) 
        : stats(10, 3, 2)
        {
            this->stats.xp = 0;
            this->stats.level = 1;
            this->stats.maxHp = 10;
    
            type = EntityType::PLAYER;
            name = "Player";
            pos = _pos;
        }

        const Systems::Inventory& getInventory() { return inventory; };
        Stats& getStats() { return stats; };
        const Utils::Position& getPos() override { return pos; }
        void setPos(Utils::Position) override;
        const std::string& getName() override { return name; };
        const EntityType getType()override{ return type; };

        void render(const Core::Game& g) override;

        void attack(std::shared_ptr<Enemy> e);
        bool isPlayerProtecting() { return isProtecting; };
        void setPlayerProtecting() { isProtecting = true; }
        void heal(int amount);

        double damageWithProtect(int amount);

        void move(Core::Game& g,Utils::Direction dir);
        bool run(const int rand1,const int rand2);
        void collect(std::unique_ptr<Core::Board> board, Utils::Position pos);
        std::shared_ptr<Enemy> getNearEnemy(std::unique_ptr<Core::Board> board);

    private:
        Stats stats;
        Systems::Inventory inventory;
        bool isProtecting = false;
    };
}