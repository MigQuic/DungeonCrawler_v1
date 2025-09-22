#include "../include/LooterMonster.h"
#include "../include/Grid.h"

LooterMonster::LooterMonster(int x, int y, int hp) : Monster(x, y, hp)
{
    m_sym = 'L';
}

// For now, the LooterMonster can just move randomly.
void LooterMonster::update([[maybe_unused]] char command, const Grid& grid)
{
    // TODO: Implement LooterMonster AI.
    // It could move randomly or towards items if you add them.
}