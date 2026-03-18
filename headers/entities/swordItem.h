#pragma once

#include "item.h"

namespace Entities {

    class SwordItem : public Item
    {
    public:
        SwordItem(const std::string& _name,float _damage,Utils::Position _pos) : 
        name(_name),damage(_damage)
        {
            name = "sword";
            pos = _pos;
        };

        const float getDamage() { return damage; }
        const Utils::Position& getPos() override { return pos; }
        void setPos(Utils::Position) override;
        const std::string& getName() override { return name; };
        const EntityType getType()override{ return type; };

    private:
        std::string name;
        float damage;
    };
}