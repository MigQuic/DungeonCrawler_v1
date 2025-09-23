#pragma once
#include "Monster.h"

// Forward-declare Player and Grid
class Grid;
class Player;

class LooterMonster : public Monster
{
public:
    LooterMonster(int x, int y, int hp);

protected:
    // Implement the primitive operation for fleeing
    std::pair<int, int> getMoveDirection(const Player& player) const override;
};