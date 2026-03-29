#include "entities/enemy.h"


void Entities::Enemy::setHp(const int amount)
{
    stats.healthPoint = (amount < 0) ? 0 : amount;
}

void Entities::Enemy::render(const Core::Game& g)
{
    SDL_Rect rect = { pos.y * 32, pos.x * 32, 32, 32 };

    SDL_Texture* tex = g.textureManager.get("enemy");

    if (tex)
        SDL_RenderCopy(g.WindowRenderer.renderer, tex, nullptr, &rect);
    else
    {
        SDL_SetRenderDrawColor(g.WindowRenderer.renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(g.WindowRenderer.renderer, &rect);
    }
}

void Entities::Enemy::attack(std::shared_ptr<Player> p)
{
    double attackAmount = getStats().attackPoint;
    double finalDamage;

    if (p->isPlayerProtecting()) {
        finalDamage = p->damageWithProtect(attackAmount);
    } else {
        double defense = p->getStats().defensePoint;
        finalDamage = attackAmount * (100.0 / (100.0 + defense));
    }

    double playerHp = p->getStats().healthPoint;
    playerHp -= finalDamage;
    if (playerHp < 0) playerHp = 0;

    p->getStats().healthPoint = playerHp;
}

void Entities::Enemy::chase(Core::Game& g,std::shared_ptr<Entities::Player> p)
{
    auto e_pos = pos;
    auto playerPos = p->getPos();
    
    if (e_pos.x < playerPos.x)
        move(g, Utils::Direction::DOWN);
    else if (e_pos.x > playerPos.x)
        move(g, Utils::Direction::UP);

    if (e_pos.y < playerPos.y)
        move(g, Utils::Direction::RIGHT);
    else if (e_pos.y > playerPos.y)
        move(g, Utils::Direction::LEFT);
}

void Entities::Enemy::patrol(Core::Game& g)
{
    Utils::Direction dir = Utils::getRandDir();
    move(g,dir);
}

void Entities::Enemy::setPos(const Utils::Position pos)
{
    this->pos = pos;
}

void Entities::Enemy::move(Core::Game& game,Utils::Direction dir)
{
    auto currentPos = this->pos;
    auto targetPos = Utils::getDirection(currentPos.x,currentPos.y,dir);
    auto& board = game.board;

    if (!board->isTileWalkable(targetPos)) return;

    auto targetEntity = board->getEntityAt(targetPos);

    if (targetEntity && targetEntity->getType() == Entities::EntityType::PLAYER)
    {
        Systems::StartFight(game, shared_from_this());
        return;
    }

    board->setEntityAt(targetPos, shared_from_this());
    board->deleteEntityAt(currentPos);
    setPos(targetPos);
}

