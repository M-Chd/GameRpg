#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>
#include <iostream>

namespace Core {

    struct TextureManager
    {
        SDL_Renderer* renderer = nullptr;
        std::unordered_map<std::string, SDL_Texture*> textures;

        bool init(SDL_Renderer* r);

        bool load(const std::string& id, const std::string& path);
        SDL_Texture* get(const std::string& id) const;

        void clear();
    };

}