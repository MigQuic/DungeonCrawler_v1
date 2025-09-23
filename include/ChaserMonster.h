#pragma once
#include "Monster.h"

// Forward-declare Player and Grid
class Player;
class Grid;

class ChaserMonster : public Monster
{
public:
    ChaserMonster(int x, int y, int hp);

protected:
    std::pair<int, int> getMoveDirection(const Player &player) const override;
};