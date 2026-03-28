#pragma once
#include "item.h"

namespace Entities{

    class HealItem : public Item
    {
    public:
        HealItem(const std::string& _name,float _healAmmount,Utils::Position _pos) : Item(_name,_pos),healAmmount(_healAmmount)
        {
            Item::type = EntityType::HEAL;
        };

        const float& getAmmount() { return healAmmount; }
        void setAmmount(float a) { if (a > 0) healAmmount = a; }

        const Utils::Position& getPos() override { return pos; }
        const std::string& getName() override { return name; };
        const EntityType getType()override{ return type; };
        void setPos(Utils::Position pos) override { this->pos = pos; }

        void render(const Core::Game& g) override;

    private:
        float healAmmount;
    };
}