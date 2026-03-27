#include "systems/input.h"

bool Systems::is_key_pressed(int scancode){
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    return keys[scancode];
}