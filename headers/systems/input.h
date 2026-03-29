#define SDL_MAIN_HANDLED
#pragma once
#include <SDL2/SDL.h>

namespace Systems
{
    bool is_key_pressed(int scancode);
}