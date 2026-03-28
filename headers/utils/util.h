#pragma once
#include "direction.h"
#include "position.h"
#include "core/board.h"
#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/healItem.h"
#include <math.h>
#include <random>

namespace Core
{ 
    class Board;
}

namespace Entities
{
    class Player;
    class Enemy;
}

namespace Utils {

    static const std::string names[8] = {"Miku","Teto","Neru","Dante","Rosalina","Borat","GojoTurk","Bunbun"};
    
    Direction getRandDir();
    Position generateRandomPosition(Core::Board& board);
    Position getDirection(int posX, int posY, Utils::Direction dir);
    std::string generateRandomName();
    int calculateDistance(std::shared_ptr<Entities::Enemy> mob,std::shared_ptr<Entities::Player> player);
    std::vector<Entities::HealItem>& getHealInBoard(Core::Board& b);
    void HealPlayerOnItem(std::shared_ptr<Entities::Player> player, Core::Board& board, Position pos);
}