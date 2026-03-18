#pragma once

namespace Entities {

    class Stats
    {
        int healthPoint;
        int attackPoint;
        int defensePoint;
        int xp;
        int level;
        int maxHp = 30;

        Stats(int _hp,int _attack,int _defense = 2) : healthPoint(_hp), attackPoint(_attack),
            defensePoint(_defense){}

    private:
        void checkLvlUp();
        void gainXp(int amount);
        int getXpToNxtLvl();

    };
}