#pragma once
#include "Entity.h"

class Grid;     // forward-declare

class Monster : public Entity {
    public:
        Monster(int x, int y, int hp);

        // still can do AI later
        void update(int command, const Grid& grid) override;     
};