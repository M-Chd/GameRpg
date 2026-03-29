#include "entities/healItem.h"

void Entities::HealItem::render(const Core::Game& g)
{
    SDL_Rect rect = { pos.y * 32, pos.x * 32, 32, 32 };

    SDL_Texture* tex = g.textureManager.get("heal");

    if (tex)
        SDL_RenderCopy(g.WindowRenderer.renderer, tex, nullptr, &rect);
    else
    {
        SDL_SetRenderDrawColor(g.WindowRenderer.renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(g.WindowRenderer.renderer, &rect);
    }
}