#pragma once
#include "entity.h"
#include "stats.h"
#include "enemyState.h"
#include "utils/position.h"
#include "player.h"
#include <iostream>
#include <string>


namespace Entities{

    class Enemy : public IEntity
    {
    public:
        
        Enemy(const std::string _name,Stats _stats,Utils::Position _pos) : stats(_stats)
        {
            name = _name;
            pos = _pos;
        }

        EnemyState getState() { return state; };
        const Stats& getStats() { return stats; }
        
        const Utils::Position& getPos() override { return pos; };
        void setPos(Utils::Position p) override;
        const std::string& getName() override { return name; };
        const EntityType getType()override{ return type; };
        
        void attack(std::shared_ptr<Player> e);
        void chase();
        void patrol();

        void move(Core::Board& b);
        void collect(Core::Board& b, Utils::Position pos);

        void setState(EnemyState state) { this->state = state; };

        virtual void update() override;
        virtual void render(SDL_Renderer* renderer) override;

    private:
        Stats stats;
        EnemyState state;
    };
}