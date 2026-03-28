#pragma once

#include "item.h"
#include "core/game.h"

namespace Entities {

    class SwordItem : public Item
    {
    public:
        SwordItem(const std::string& _name,float _damage,Utils::Position _pos) : Item(_name,_pos),damage(_damage)
        {};

        const float getDamage() { return damage; }
        const Utils::Position& getPos() override { return pos; }
        void setPos(Utils::Position pos) override { this->pos = pos; }
        const std::string& getName() override { return name; };
        const EntityType getType()override{ return type; };

        void render(const Core::Game& g) override;

    private:
        float damage;
    };
}