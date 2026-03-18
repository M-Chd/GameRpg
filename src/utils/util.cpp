#include "utils/util.h"


Utils::Direction getRandDir()
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