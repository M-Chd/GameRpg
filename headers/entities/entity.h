#pragma once
#include <SDL2/SDL.h>

namespace Entities {

    class IEntity
    {
    public:
        virtual void update() = 0;
        virtual void render(SDL_Renderer* renderer) = 0;

        virtual ~IEntity() = default;

    };
}