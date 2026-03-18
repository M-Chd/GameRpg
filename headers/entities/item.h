#pragma once
#include "entity.h"
#include "utils/position.h"
#include <iostream>

namespace Entities{

    class Item : public IEntity
    {
    public:

        Item(std::string _name,Utils::Position _pos)
        {
            name = _name;
            pos = _pos;
        };

        const Utils::Position& getPos() override { return pos; }
        void setPos(Utils::Position) override;
        const std::string& getName() override { return name; };
        const EntityType getType()override{ return type; };

        void update();
        void render(SDL_Renderer* renderer);

    };
}