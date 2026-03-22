#include "entities/player.h"

void Entities::Player::setPos(Utils::Position p)
{
    this->pos = p;
}

void Entities::Player::attack(std::shared_ptr<Enemy> e)
{

}

void Entities::Player::heal(int amount)
{
    this->stats.healthPoint += amount;
}

void Entities::Player::update()
{

}

void Entities::Player::render(SDL_Renderer* renderer)
{

}



