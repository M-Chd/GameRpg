#pragma once
#include <SDL2/SDL.h>
#include "utils/direction.h"
#include <unordered_map>

namespace Systems
{

    const std::unordered_map<SDL_Scancode, Utils::Direction> keyToDirection = {
        /// arrows
        {SDL_SCANCODE_UP, Utils::Direction::UP},
        {SDL_SCANCODE_DOWN, Utils::Direction::DOWN},
        {SDL_SCANCODE_LEFT, Utils::Direction::LEFT},
        {SDL_SCANCODE_RIGHT, Utils::Direction::RIGHT},

        // WASD (QWERTY)
        {SDL_SCANCODE_W, Utils::Direction::UP},
        {SDL_SCANCODE_A, Utils::Direction::LEFT},
        {SDL_SCANCODE_S, Utils::Direction::DOWN},
        {SDL_SCANCODE_D, Utils::Direction::RIGHT},

        // ZQSD (AZERTY)
        {SDL_SCANCODE_Z, Utils::Direction::UP},
        {SDL_SCANCODE_Q, Utils::Direction::LEFT}};
}