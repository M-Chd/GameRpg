#pragma once
#include <string>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <unordered_map>
#include <memory>

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

            void setEntityAt(Position pos,std::shared_ptr<Entity> e);
            void deleteEntityAt(Position pos);
            void getEntityTypeAt(Position pos) const;
            void std::unordered_map<Position,std::shared_ptr<Entity>>& getEntities() const;
            
            bool isTileWalkable(Position pos);

            std::pair<short,short> getBoardSizes() const;
            
        private:
            std::vector<Entity> entities;


    }
}