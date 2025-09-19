#pragma once
#include "Entity.h"

class Monster : public Entity {
    public:
        Monster(int x, int y, int hp);

        // still can do AI later
        void update(char command, const Grid& grid) override;     
};