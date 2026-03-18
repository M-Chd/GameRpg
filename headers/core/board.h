#pragma once
#include <string>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <memory>
#include "utils/position.h"
#include "entities/entity.h"

namespace Core 
{
    class Board 
    {
    private:

        const short BOARDSIZE = 19;
        const short TILESIZE = 32;

    public:

        Board();
        ~Board();

        void setEntityAt(Utils::Position pos,std::shared_ptr<Entities::IEntity> e);
        void deleteEntityAt(Utils::Position pos);
        Entities::EntityType getEntityTypeAt(Utils::Position pos) const;
        std::shared_ptr<Entities::IEntity> getEntityAt(Utils::Position p);
        const std::vector<std::shared_ptr<Entities::IEntity>>& getEntities() { return entities; };
            
        bool isTileWalkable(Utils::Position pos);

        std::tuple<short,short> getBoardSizes() const { return {BOARDSIZE,TILESIZE}; }
            
    private:
        std::vector<std::shared_ptr<Entities::IEntity>> entities;

    };
}