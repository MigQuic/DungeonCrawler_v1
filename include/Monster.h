#pragma once
#include "Entity.h"
#include <utility> // For std::pair

// Forward-declare Player and Grid to avoid including the full headers
class Player;
class Grid;

class Monster : public Entity
{
public:
    Monster(int x, int y, char sym, int hp) : Entity(x, y, sym, hp) {}

    // Monsters don't take commands, so we override the base update to do nothing.
    void update([[maybe_unused]] char command, [[maybe_unused]] const Grid &grid) override {}

    // This is the "Template Method" - it's public and non-virtual.
    // It calls the primitive `getMoveDirection` to do the custom work.
    void update(const Player &player, const Grid &grid);

protected:
    // This is the "primitive operation" that subclasses MUST implement to define their AI.
    virtual std::pair<int, int> getMoveDirection(const Player &player) const = 0;
};