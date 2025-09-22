#pragma once
#include "Entity.h"

class Monster : public Entity {
public:
    // Define the constructor inline to provide its implementation.
    // It calls the base Entity constructor with a default symbol 'M'.
    Monster(int x, int y, int hp) : Entity(x, y, 'M', hp) {}

    void update(char command, const Grid& grid) override = 0;
};