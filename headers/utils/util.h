#pragma once
#include "direction.h"
#include "position.h"
#include "core/board.h"
#include "entities/player.h"
#include "entities/enemy.h"
#include <random>

namespace Utils {

    Direction getRandDir();

    const std::string names[] = {"Miku","Teto","Neru","Dante","Rosalina","Borat","GojoTurk","Bunbun"};

    Position generateRandomPosition(int boardSize, Core::Board& board);
    Position generateRandomItemPosition(int boardSize, Core::Board& board);
    std::string generateRandomName();

    int calculateDistance(std::shared_ptr<Entities::Enemy> mob,std::shared_ptr<Entities::Player> player);
}