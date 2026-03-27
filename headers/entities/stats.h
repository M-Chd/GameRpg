#pragma once

namespace Entities {

    struct Stats
    {
        int healthPoint;
        int attackPoint;
        int defensePoint;
        int xp = 0;
        int level = 1;
        int maxHp = 30;

        Stats(int _hp,int _attack,int _defense = 2) : healthPoint(_hp), attackPoint(_attack),
            defensePoint(_defense){}
            
        void checkLvlUp();
        void gainXp(int amount);
        int getXpToNxtLvl();

    };
}