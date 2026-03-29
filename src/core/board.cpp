#include "core/board.h"

void Core::Board::setEntityAt(Utils::Position pos, std::shared_ptr<Entities::IEntity> e)
{
    if (!e) {
        deleteEntityAt(pos);
        return;
    }

    if (pos.x < 0 || pos.y < 0 || pos.x >= boardSize.boardSize || pos.y >= boardSize.boardSize)
    {
        std::cerr << "Invalid Position: (" << pos.x << ", " << pos.y << ")" << std::endl;
        return;
    }

    deleteEntityAt(pos);

    e->setPos(pos);
    entities.push_back(e);
}

void Core::Board::deleteEntityAt(Utils::Position pos)
{
    for (auto it = entities.begin(); it != entities.end(); ) {
        if ((*it)->getPos() == pos) {
            it = entities.erase(it);
        } else {
            ++it;
        }
    }
}

std::shared_ptr<Entities::IEntity> Core::Board::getEntityAt(Utils::Position pos) const
{
    for (auto& e : entities)
        if (e->getPos() == pos)
            return e;
    return nullptr;
}

Entities::EntityType Core::Board::getEntityTypeAt(Utils::Position pos) const
{
    auto e = getEntityAt(pos);
    return e ? e->getType() : Entities::EntityType::NONE;
}

bool Core::Board::isTileWalkable(Utils::Position pos) const
{
    auto type = getEntityTypeAt(pos);
    return type == Entities::EntityType::NONE || type == Entities::EntityType::PLAYER
    || type == Entities::EntityType::HEAL || type == Entities::EntityType::ITEM;
}

std::vector<std::shared_ptr<Entities::Enemy>> Core::Board::getEnemies() const
{
    std::vector<std::shared_ptr<Entities::Enemy>> enemies;
    for (auto& e : entities)
    {
        if (e->getType() == Entities::EntityType::ENEMY)
            enemies.push_back(std::dynamic_pointer_cast<Entities::Enemy>(e));
    }
    return enemies;
}

std::vector<std::shared_ptr<Entities::IEntity>> Core::Board::getEntities() const
{
    return entities;
}