#pragma once
#include "item.h"

namespace Entities{

    class HealItem : public Item
    {
    public:
        HealItem(const std::string& _name,float _healAmmount,Utils::Position _pos) : healAmmount(_healAmmount)
        {
            name = _name;
            pos = _pos;
        };

        const float& getAmmount() { return healAmmount; }
        void setAmmount(float a) { if (a > 0) healAmmount = a; }

        const Utils::Position& getPos() override { return pos; }
        void setPos(Utils::Position) override;
        const std::string& getName() override { return name; };
        const EntityType getType()override{ return type; };

    private:
        float healAmmount;
    };
}