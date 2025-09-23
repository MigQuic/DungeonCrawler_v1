#include "../include/Monster.h"
#include "../include/Grid.h"
#include "../include/Player.h"
#include <utility> // For std::pair

void Monster::update(const Player &player, const Grid &grid)
{
    // Delegate the "how to move" decision to the subclass
    std::pair<int, int> direction = getMoveDirection(player);
    int dx = direction.first;
    int dy = direction.second;

    int newX = m_x + dx;
    int newY = m_y + dy;

    if (!grid.isWall(newX, newY))
    {
        setPosition(newX, newY);
    }
}