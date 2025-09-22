#pragma once
#include "Monster.h"
#include "Player.h"

class ChaserMonster : public Monster
{
public:
    ChaserMonster(int x, int y, int hp);

    /*
        The AI for this specific monster type.
        It needs to about the player to chase it.
    */

    void update(const Player &player, const Grid &grid);
    void update(char command, const Grid &grid) override; // ??
};