#include "../include/ChaserMonster.h"
#include "../include/Grid.h"

ChaserMonster::ChaserMonster(int x, int y, int hp) : Monster(x, y, hp)
{
    m_sym = 'C';
}

void ChaserMonster::update(const Player &player, const Grid &grid) {
    int playerX = player.getX();
    int playerY = player.getY();

    int dx = 0; 
    int dy = 0;

    if (playerX < m_x) dx = -1;
    else if (playerX > m_x) dx = 1;

    if (playerY < m_y) dy = -1;
    else if (playerY > m_y) dy = 1;

    int newX = m_x + dx;
    int newY = m_y + dy;

    if (!grid.isWall(newX, newY)){
        setPosition(newX, newY);
    }
}

// must implement this but maybe i'll delegate it later.
void ChaserMonster::update([[maybe_unused]]char command, [[maybe_unused]] const Grid& grid){}