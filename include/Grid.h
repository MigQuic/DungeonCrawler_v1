#pragma once
#include <string>
#include <vector>

// Forward-declare Entity so we can use it in the draw method signature
class Entity;

class Grid
{
public:
    Grid(int rows, int cols);

    // Draws the map and stamps the given entities on top
    void draw(const std::vector<const Entity*>& entities) const;
    void clearScreen() const; // A simple way to clear the console
    bool isWall(int x, int y) const;

    int width() const;
    int height() const;

private:
    std::vector<std::string> m_cells;
};
