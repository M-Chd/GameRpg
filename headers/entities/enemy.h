#pragma once
#include "entity.h"
#include "stats.h"
#include "enemyState.h"
#include "utils/position.h"
#include "player.h"
#include <iostream>
#include <string>


namespace Entities{

    class Enemy : public IEntity, public std::enable_shared_from_this<Enemy>
    {
    public:
        
        Enemy(const std::string _name,Stats _stats,Utils::Position _pos) : stats(_stats)
        {
            type = EntityType::ENEMY;
            name = _name;
            pos = _pos;
        }

        EnemyState getState() { return state; };
        const Stats& getStats() { return stats; }
        
        const Utils::Position& getPos() override { return pos; };
        void setPos(Utils::Position p) override;
        const std::string& getName() override { return name; };
        const EntityType getType()override{ return type; };

        void render(const Core::Game& g) override;

        void setHp(const int amount);
        
        void attack(std::shared_ptr<Player> p);
        void chase(Core::Game& g,std::shared_ptr<Player> p);
        void patrol();

        void move(Core::Game& g, Utils::Direction dir);
        //void collect(Core::Board& b, Utils::Position pos);

        void setState(EnemyState state) { this->state = state; }

    private:
        Stats stats;
        EnemyState state = EnemyState::PATROL;
    };
}