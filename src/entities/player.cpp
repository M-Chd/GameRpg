#include "entities/player.h"

void Entities::Player::setPos(Utils::Position p)
{
    this->pos = p;
}

void Entities::Player::attack(std::shared_ptr<Enemy> e)
{
    double EnemyDefense = e->getStats().defensePoint;
    double damage = stats.attackPoint * (100.0 / (100.0 + EnemyDefense));

    if (e->getStats().healthPoint > 0)
    {
        e->setHp(e->getStats().healthPoint - damage);
    }
}

void Entities::Player::heal(int amount)
{
    this->stats.healthPoint += amount;
}

void Entities::Player::collect(Core::Board&  b, Utils::Position pos)
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

bool Entities::Player::run(const int rand1, const int rand2)
{

    auto hp = stats.healthPoint;
    auto maxhp = stats.maxHp;

    if (hp == maxhp){
        return true;
    }
    else if (hp > maxhp/2){
        if (rand1 == 1){
            return true;
        }
        return false;
    }
    else if (hp < maxhp/2){
        if (rand2 == 0){
            return false;
        }
        return true;
    } 
    else {
        return ((rand() % 4) == 3);
    }
}

void Entities::Player::move(Core::Game& game, Utils::Direction dir)
{
    auto currentPos = this->pos;
    auto targetPos = Utils::getDirection(currentPos.x, currentPos.y, dir);
    auto& board = game.board;

    if (!board->isTileWalkable(targetPos)) return;

    auto targetEntity = board->getEntityAt(targetPos);

    if (!targetEntity) {
        board->setEntityAt(targetPos, shared_from_this());
        board->deleteEntityAt(currentPos);
        setPos(targetPos);
        return;
    }

    switch (targetEntity->getType()) {
        case Entities::EntityType::ITEM:
            collect(*board, targetPos);
            break;

        case Entities::EntityType::HEAL:
            Utils::HealPlayerOnItem(shared_from_this(), *board, targetPos);
            break;

        case Entities::EntityType::ENEMY: {
            auto mob = std::dynamic_pointer_cast<Entities::Enemy>(targetEntity);
            Systems::StartFight(game, mob);
            break;
        }
        default:
            break;
    }
}

void Entities::Player::render(const Core::Game& g)
{
    SDL_Rect rect = { pos.y * 32, pos.x * 32, 32, 32 };

    SDL_Texture* tex = g.textureManager.get("player");

    if (tex)
        SDL_RenderCopy(g.WindowRenderer.renderer, tex, nullptr, &rect);
    else
    {
        SDL_SetRenderDrawColor(g.WindowRenderer.renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(g.WindowRenderer.renderer, &rect);
    }
}

double Entities::Player::damageWithProtect(int amount)
{
    if (!isPlayerProtecting()){
        return 0;
    }
    double damageReductionFactor = 0.5; // 50% of shield protection
    double newAttackAmount = amount * damageReductionFactor;

    return newAttackAmount;
}

std::shared_ptr<Entities::Enemy> Entities::Player::getNearEnemy(Core::Board& b)
{
    auto playerPos = pos;

	for (int x = playerPos.x - 2; x <= playerPos.x + 2; ++x) {
		for (int y = playerPos.y - 2; y <= playerPos.y + 2; ++y) {
			if (x >= 0 && x < b.getBoardSizes().boardSize && y >= 0 && y < b.getBoardSizes().boardSize) {
				auto enemy = b.getEntityAt({x,y});
				if (enemy && enemy->getType() == EntityType::ENEMY) {
					return std::dynamic_pointer_cast<Entities::Enemy>(enemy);
				}
			}
		}
	}
	return nullptr;
}



