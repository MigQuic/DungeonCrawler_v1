#pragma once
#include "Monster.h"
#include "Player.h"

class LooterMonster : public Monster
{
public:
    LooterMonster(int x, int y, int hp);

    void update(char command, const Grid& grid) override;
};