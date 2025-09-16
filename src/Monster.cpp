#include "../include/Monster.h"


// Forward everything to Entity(x,y,sym,hp)
Monster::Monster(int x, int y, int hp)
  : Entity(x, y, 'M', hp) // the monster had ' ' in the sym 'M'
{}

void Monster::update(int command, const Grid& /*grid*/) {
    // no-op for now; can add AI later
}