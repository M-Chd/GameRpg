#include "utils/util.h"


Utils::Direction Utils::getRandDir()
{
    int nbr = rand() % 4;

    switch (nbr)
    {
    case 0:
        return Utils::Direction::DOWN;
        break;
    case 1:
        return Utils::Direction::UP;
        break;
    case 2:
        return Utils::Direction::LEFT;
        break;
    case 3:
        return Utils::Direction::RIGHT;
        break;
    }
}

int Utils::calculateDistance(std::shared_ptr<Entities::Enemy> e, std::shared_ptr<Entities::Player> p)
{
    return sqrt( ( pow( (p->getPos().x - e->getPos().x), 2) + pow( (p->getPos().y - e->getPos().y), 2) ) );
}

std::string Utils::generateRandomName()
{
    return names[rand() % 8];
}

Utils::Position generateRandomPosition(Core::Board& board)
{
    std::random_device rd; 
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, board.getBoardSizes().boardSize - 1);

    int x = distr(eng);
    int y = distr(eng);

    if (board.getEntityTypeAt({x,y}) != Entities::EntityType::NONE) {
        do {
            x = distr(eng);
            y = distr(eng);
        } while (board.getEntityTypeAt({x,y}) == Entities::EntityType::NONE);
    }
    return { x , y };
}

std::vector<Entities::HealItem>& Utils::getHealInBoard(Core::Board& b)
{
    std::vector<Entities::HealItem> Heals;
    
    for (const auto &e : b.getEntities())
    {
        if (e->getType() == Entities::EntityType::ITEM){
            if (dynamic_cast<Entities::HealItem*>(e.get())){
                Heals.emplace_back(e);
            }
        }
    }
    return Heals;
}