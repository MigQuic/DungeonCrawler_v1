#include "../include/Player.h"
#include "../include/Grid.h"
#include <iostream>
#include <cctype>

Player::Player(int x, int y, int hp) : Entity(x, y, '@', hp)
{
}

// -------------------------------------------------

void Player::update(char command, const Grid &grid)
{
    // The command is already a char, so we just need to ensure it's lowercase.
    char move_cmd = static_cast<char>(std::tolower(command));

    // 1) Compute delta
    int dx = 0, dy = 0;
    switch (move_cmd)
    {
    case 'w':
        dy = -1;
        break;
    case 's':
        dy = 1;
        break;
    case 'a':
        dx = -1;
        break;
    case 'd':
        dx = 1;
        break;
    default:
        return; // ignore unrecognized keys
    }

    // 2) Attempt move
    int newX = m_x + dx, newY = m_y + dy;
    if (!grid.isWall(newX, newY))
    {
        m_x = newX;
        m_y = newY;
    }
}
