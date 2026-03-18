#pragma once
#include <SDL2/SDL.h>
#include "entityType.h"

namespace Entities {

    class IEntity
    {
    public:
        virtual void update() = 0;
        virtual void render(SDL_Renderer* renderer) = 0;

        virtual const Utils::Position& getPos() = 0;
        virtual void setPos(Utils::Position p) = 0;
        virtual const std::string& getName() = 0;
        virtual const EntityType getType() = 0;

        virtual ~IEntity() = default;

    protected:
        Utils::Position pos;
        EntityType type;
        std::string name;

    };
}