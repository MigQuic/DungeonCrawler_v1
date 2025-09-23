#include "../include/LooterMonster.h"
#include "../include/Grid.h"
#include "../include/Player.h"

LooterMonster::LooterMonster(int x, int y, int hp) : Monster(x, y, 'L', hp) {}

std::pair<int, int> LooterMonster::getMoveDirection(const Player& player) const
{
    // Locate the player
    int playerX = player.getX();
    int playerY = player.getY();

    int dx = 0;
    int dy = 0;

    // Move away from the player
    if (playerX < m_x)
        dx = 1;
    else if (playerX > m_x)
        dx = -1;
    if (playerY < m_y)
        dy = 1;
    else if (playerY > m_y)
        dy = -1;

    return {dx, dy};
}