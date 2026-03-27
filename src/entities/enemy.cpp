#include "entities/enemy.h"


void Entities::Enemy::setHp(const int amount)
{
    if (amount < 0) return;

    stats.healthPoint = amount;
}

void Entities::Enemy::attack(std::shared_ptr<Player> p)
{

}

void Entities::Enemy::chase()
{

}

void Entities::Enemy::patrol()
{

}

void Entities::Enemy::setPos(const Utils::Position pos)
{
    this->pos = pos;
}

void Entities::Enemy::move(Core::Board& b)
{
    
}

