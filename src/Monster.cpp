#include "../include/Monster.h"

// Forward everything to Entity(x,y,sym,hp)
Monster::Monster(int x, int y, int hp) : Entity(x, y, 'M', hp)
{
}

void Monster::update([[maybe_unused]] int command, [[maybe_unused]] const Grid &grid)
{
  // no-op for now; can add AI later
}