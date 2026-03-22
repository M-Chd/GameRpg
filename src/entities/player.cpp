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

void Entities::Player::collect(Core::Board& b, Utils::Position pos)
{
    auto item = b.getEntityAt(pos);
    if (!item) {
        std::cerr << "No entity in this position" << std::endl;
        return;
    }
    auto itemPtr = std::dynamic_pointer_cast<Entities::Item>(item);
    if (!itemPtr) {
        std::cerr << "Entity is not an Item" << std::endl;
        return;
    }
    inventory.addItem(itemPtr);
    b.setEntityAt(pos, nullptr);
    
    std::cout << "Item " << itemPtr->getName() << " collected" << std::endl;
}

void Entities::Player::update()
{

}

void Entities::Player::render(SDL_Renderer* renderer)
{

}



