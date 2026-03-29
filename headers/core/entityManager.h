#pragma once
#include <iostream>
#include "core/board.h"
#include "entities/player.h"
#include "entities/healItem.h"
#include "utils/util.h"

namespace Entities { class Player; }

namespace Core {

    struct Game;
    class Board;

    struct EntityManager
    {
    private:
        int playerBasedHp(std::shared_ptr<Entities::Player> player);
        double playerBasedAttack(std::shared_ptr<Entities::Player> player);
        double playerBasedDefense(std::shared_ptr<Entities::Player> player);
        double playerBasedHealAmmount(std::shared_ptr<Entities::Player> player);
    public:
        void spawnEnemy(Core::Board& board,std::shared_ptr<Entities::Player> player);
        void spawnHeal(Core::Board& board,std::shared_ptr<Entities::Player> player);
        void enemyAlgorithm(Core::Game& g);
        void initEntities(Core::Game& g);
    };
}