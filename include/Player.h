#pragma once
#include "Entity.h"

class Player : public Entity {
public:
    Player(int x, int y, int hp);
    void update(const Grid& grid) override;     // reads w/a/s/d
};