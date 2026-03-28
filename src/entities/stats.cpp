#include "entities/stats.h"

void Entities::Stats::gainXp(int amount)
{
    if (amount > 0)
    {
        xp += amount;
        checkLvlUp();
    }
}

void Entities::Stats::checkLvlUp()
{
    int threshold = level * 10;
    while (xp >= threshold) {
        xp -= threshold;
        level++;
        maxHp += 5;
        hp = maxHp;
        attack += 2;
        defense += 0.5;
        std::cout << "Level Up !" << std::endl;

        threshold = level * (2 * level);
    }
}

void Entities::Stats::getXpToNxtLvl()
{
    int threshold = level * 10;
    return threshold - xp;
}