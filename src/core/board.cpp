#include "core/board.h"

void Core::Board::setEntityAt(Utils::Position pos, std::shared_ptr<Entities::IEntity> e)
{
    if(!e) return;

    if (pos.x >= 0 && pos.y < size.boardSize &&
        pos.y >= 0 && pos.y < size.boardSize)
    {
        e->setPos(pos);
        entities.push_back(e);
    } else
        std::cerr << "Invalid Position:  (" << pos.x << ", " << pos.y << ")" << std::endl;
}

void Core::Board::deleteEntityAt(Utils::Position p)
{

    auto it = entities.begin();

    while (it != entities.end())
    {
        if((*it)->getPos() == p)
        {
            entities.erase(it);
            break;
        }
        it++;
    }
}

Entities::EntityType Core::Board::getEntityTypeAt(Utils::Position p) const
{
    
    for (const auto& e : entities)
    {
        if (e->getPos() == p)
        {
            return e->getType();
        }
    }
    return Entities::EntityType::NONE;
}

bool Core::Board::isTileWalkable(Utils::Position p)
{

    auto type = getEntityTypeAt(p);

    if (type != Entities::EntityType::NONE &&
        type != Entities::EntityType::PLAYER)
    {
        return false;
    }
    return true;
}

std::shared_ptr<Entities::IEntity> Core::Board::getEntityAt(Utils::Position p)
{
    for (const auto& e : entities)
    {
        if (e->getPos() == p)
        {
            return e;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Entities::Enemy>>& Core::Board::getEnemies() const{

    std::vector<std::shared_ptr<Entities::Enemy>> enemies;
    
    for (const auto& e : entities)
    {
        if (e->getType() == Entities::EntityType::ENEMY)
        {
            enemies.emplace_back(e);
        }
    }
    return enemies;
}