#include "../include/ChaserMonster.h"
#include "../include/Grid.h"
#include "../include/Player.h"

ChaserMonster::ChaserMonster(int x, int y, int hp) : Monster(x, y, 'C', hp) {}

std::pair<int, int> ChaserMonster::getMoveDirection(const Player &player) const
{
    // Locate the player
    int playerX = player.getX();
    int playerY = player.getY();

    int dx = 0;
    int dy = 0;

    // Chase the player
    if (playerX < m_x)
        dx = -1;
    else if (playerX > m_x)
        dx = 1;

    if (playerY < m_y)
        dy = -1;
    else if (playerY > m_y)
        dy = 1;

    return {dx, dy};
}