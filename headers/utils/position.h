#pragma once

namespace Utils
{
    struct Position
    {
        int x,y = 0;

        bool operator==(const Position& other) const 
        {
            return x == other.x && y == other.y;
        }
    };
    
}
