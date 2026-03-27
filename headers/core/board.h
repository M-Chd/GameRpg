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
#include "entities/enemy.h"

namespace Core 
{
    struct Size
    {
        short boardSize = 19;
        short tileSize = 32;
    };

    class Board 
    {
    private:

        Size size;

    public:

        Board();
        ~Board();

        void setEntityAt(Utils::Position pos,std::shared_ptr<Entities::IEntity> e);
        void deleteEntityAt(Utils::Position pos);
        Entities::EntityType getEntityTypeAt(Utils::Position pos) const;
        std::shared_ptr<Entities::IEntity> getEntityAt(Utils::Position p);
        const std::vector<std::shared_ptr<Entities::IEntity>>& getEntities() { return entities; };
        std::vector<std::shared_ptr<Entities::Enemy>>& getEnemies() const;
            
        bool isTileWalkable(Utils::Position pos);

        Size getBoardSizes() const { return size; }
            
    private:
        std::vector<std::shared_ptr<Entities::IEntity>> entities;

    };
}