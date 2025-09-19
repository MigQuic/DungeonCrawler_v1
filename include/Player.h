#pragma once
#include "Entity.h"

class Player : public Entity {
public:
    Player(int x, int y, int hp);
    
    void update(char command, const Grid& grid) override;
};