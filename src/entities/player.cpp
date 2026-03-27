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
        e->setHp(stats.healthPoint - damage);
    }
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

void Entities::Player::update()
{

}

void Entities::Player::render(SDL_Renderer* renderer)
{

}

std::shared_ptr<Entities::Enemy> Entities::Player::getNearEnemy(Core::Board& b)
{
    auto playerPos = pos;

	for (int x = playerPos.x - 2; x <= playerPos.x + 2; ++x) {
		for (int y = playerPos.y - 2; y <= playerPos.y + 2; ++y) {
			if (x >= 0 && x < b.getBoardSizes().boardSize && y >= 0 && y < b.getBoardSizes().boardSize) {
				auto enemy = b.getEntityAt({x,y});
				if (enemy && enemy->getType() == EntityType::ENEMY) {
					return std::make_shared<Entities::Enemy>(enemy);
				}
			}
		}
	}
	return nullptr;
}



