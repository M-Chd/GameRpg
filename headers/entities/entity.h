#pragma once
#include <SDL2/SDL.h>
#include "entityType.h"
#include "utils/position.h"
#include <string>

namespace Core { class Game; }

namespace Entities {

    class IEntity
    {
    public:
        virtual const Utils::Position& getPos() = 0;
        virtual void setPos(Utils::Position p) = 0;
        virtual const std::string& getName() = 0;
        virtual const EntityType getType() = 0;

        virtual ~IEntity() = default;

        virtual void render(const Core::Game& g) = 0;

    protected:
        Utils::Position pos;
        EntityType type;
        std::string name;

    };
}