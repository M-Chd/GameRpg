#include "core/entityManager.h"

void Core::EntityManager::spawnEnemy(Core::Board& board,std::shared_ptr<Entities::Player> player)
{
    int enemyHp = this->playerBasedHp(player);
    double enemyAttack = this->playerBasedAttack(player);
    double enemyDefense = this->playerBasedDefense(player);

    Utils::Position defaultPos = {0,0}; 

    auto enemy1 = std::make_shared<Entities::Enemy>(Utils::generateRandomName(),Entities::Stats(enemyHp,enemyAttack,enemyDefense),defaultPos);
    auto enemy2 = std::make_shared<Entities::Enemy>(Utils::generateRandomName(),Entities::Stats(enemyHp,enemyAttack,enemyDefense),defaultPos);
    auto enemy3 = std::make_shared<Entities::Enemy>(Utils::generateRandomName(),Entities::Stats(enemyHp,enemyAttack,enemyDefense),defaultPos);

    board.setEntityAt(Utils::generateRandomPosition(board), enemy1);
    board.setEntityAt(Utils::generateRandomPosition(board), enemy2);
    board.setEntityAt(Utils::generateRandomPosition(board), enemy3);

}

void Core::EntityManager::initEntities(Core::Game& g)
{
    int boardSize = 19;

    g.player = std::make_shared<Entities::Player>(Utils::Position{0,0});
    g.board->setEntityAt({boardSize/2,boardSize/2},g.player);

    auto sword = std::make_shared<Entities::SwordItem>("Sword",5,Utils::Position{0,0});
    Utils::Position randomPos = Utils::generateRandomPosition(*g.board);
    g.board->setEntityAt(Utils::Position{randomPos.x,randomPos.y},sword);

    spawnEnemy(*g.board,g.player);
    spawnHeal(*g.board,g.player);
}

void Core::EntityManager::spawnHeal(Core::Board& board,std::shared_ptr<Entities::Player> player)
{

    if(Utils::getHealInBoard(board).empty()){
        int playerHp = player->getStats().healthPoint;
        int playerMaxHp = player->getStats().maxHp;
    
        if (playerHp <= playerMaxHp/2){
            double amount = playerBasedHealAmmount(player);
            auto potionHeal = std::make_shared<Entities::HealItem>("Heal", amount, Utils::Position{0,0});
            board.setEntityAt(Utils::generateRandomPosition(board),potionHeal);
        }
    }
}

void Core::EntityManager::enemyAlgorithm(Core::Game& g)
{
    auto enemyList = g.board->getEnemies();

    if(!enemyList.empty()){
        Uint32 currentTime = SDL_GetTicks();

        for (const auto& e : enemyList)
        {
            if (currentTime - e->lastMoveTime > 200)
            {
                if (Utils::calculateDistance(e,g.player) <= 5)
                    e->chase(g,g.player);
                else
                    e->patrol(g);

                e->lastMoveTime = currentTime;
            }
        }
    }
}

int Core::EntityManager::playerBasedHp(std::shared_ptr<Entities::Player> player)
{
    int baseHp = 10;
    int lvl = player->getStats().level;
    return baseHp + static_cast<int>((lvl - 1) * 5 * 1.25);
}


double Core::EntityManager::playerBasedAttack(std::shared_ptr<Entities::Player> player)
{
    double attack = player->getStats().attackPoint;
    int lvl = player->getStats().level;
    if (lvl > 1){
        return attack * 0.55;
    }
    return 2.0;
}


double Core::EntityManager::playerBasedDefense(std::shared_ptr<Entities::Player> player)
{
    double defense = player->getStats().defensePoint;
    int lvl = player->getStats().level;
    if (lvl > 1){
        return defense * 1.25;
    }
    return 2.0;
}


double Core::EntityManager::playerBasedHealAmmount(std::shared_ptr<Entities::Player> player)
{
    return player->getStats().maxHp / 1.5;
}