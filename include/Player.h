#pragma once
#include "Entity.h"

class Player : public Entity {
public:
    Player(int x, int y, int hp);
    
    void update(int command, const Grid& grid) override;
};