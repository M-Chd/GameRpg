#include "core/textureManager.h"

namespace Core {

    bool TextureManager::init(SDL_Renderer* r)
    {
        renderer = r;
        return renderer != nullptr;
    }

    bool TextureManager::load(const std::string& id, const std::string& path)
    {
        SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());

        if (!tex)
        {
            std::cerr << "Failed to load texture: " << path
                      << " | Error: " << IMG_GetError() << std::endl;
            return false;
        }

        textures[id] = tex;
        return true;
    }

    SDL_Texture* TextureManager::get(const std::string& id) const
    {
        auto it = textures.find(id);

        if (it != textures.end())
            return it->second;

        return nullptr;
    }

    void TextureManager::clear()
    {
        for (auto& [id, tex] : textures)
        {
            SDL_DestroyTexture(tex);
        }

        textures.clear();
    }

}