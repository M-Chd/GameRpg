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
        
        Enemy(const std::string _name,Stats _stats,Utils::Position _pos) : 
        name(_name), stats(_stats), pos(_pos)
        {}

        std::string getName() const;
        Utils::Position getPos() const;
        EnemeyState getState() const;
        
        void attack(std::shared_ptr<Player> e);
        void chase();
        void patrol();

        void setState(EnemeyState state);

        virtual void update() override;
        virtual void render(SDL_Renderer* renderer) override;



    private:
        std::string name;
        Stats stats;
        EnemeyState state;
        Utils::Position pos;
    };
}