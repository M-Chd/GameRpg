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
    default:
        return Utils::Direction::UP;
        break;
    }
}

void Utils::HealPlayerOnItem(std::shared_ptr<Entities::Player> player, Core::Board& board, Utils::Position pos) {
	auto entity = board.getEntityAt(pos).get();
	auto healItem = dynamic_cast<Entities::HealItem*>(entity);
	if (healItem) {
		player->heal(healItem->getAmmount());
	}
}

Utils::Position Utils::getDirection(int posX, int posY, Utils::Direction dir)
{
	
    int boardsize = 19;

    switch (dir)
	{
	case Utils::Direction::RIGHT:
		posY += 1;
		if (posY >= boardsize) posY = 0;
		break;
	case Utils::Direction::LEFT:
		posY -= 1;
		if (posY < 0) posY = boardsize -1;
		break;
	case Utils::Direction::UP:
		posX -= 1;
		if (posX < 0) {
			posX = boardsize - 1;
		}
		break;
	case Utils::Direction::DOWN:
		posX += 1;
		if (posX >= boardsize) {
        	posX = 0;
    	}
	default:
		break;
	}
	return { posX, posY };
}

int Utils::calculateDistance(std::shared_ptr<Entities::Enemy> e, std::shared_ptr<Entities::Player> p)
{
    return sqrt( ( pow( (p->getPos().x - e->getPos().x), 2) + pow( (p->getPos().y - e->getPos().y), 2) ) );
}

std::string Utils::generateRandomName()
{
    return names[rand() % 8];
}

Utils::Position Utils::generateRandomPosition(Core::Board& board)
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

std::vector<std::shared_ptr<Entities::HealItem>> Utils::getHealInBoard(Core::Board& board) {
    std::vector<std::shared_ptr<Entities::HealItem>> Heals;
    auto allEntities = board.getEntities();

    for (auto& e : allEntities) {
        if (e->getType() == Entities::EntityType::HEAL) {
            auto heal = std::dynamic_pointer_cast<Entities::HealItem>(e);
            if (heal) {
                Heals.push_back(heal);
            }
        }
    }
    return Heals;
}