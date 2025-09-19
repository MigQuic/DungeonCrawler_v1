#include "../include/Grid.h"
#include "../include/Entity.h" // Provide the full definition of Entity
#include <iostream>

Grid::Grid(int rows, int cols)
{
    std::string border(cols, '#');
    m_cells.push_back(border);

    std::string middle = "#" + std::string(cols - 2, '.') + "#";
    for (int i = 0; i < rows - 2; ++i)
        m_cells.push_back(middle);

    m_cells.push_back(border);
}

void Grid::clearScreen() const
{
    // shrink the gap or swap for ANSI escape if you like
    std::cout << std::string(4, '\n');
}

void Grid::draw(const std::vector<const Entity *> &entities) const
{
    // Create a mutable copy of the grid to draw entities on
    std::vector<std::string> output_grid = m_cells;

    // "Stamp" each entity onto the output grid
    for (const auto *entity : entities)
    {
        if (entity)
        { // Ensure the pointer is not null
            output_grid[entity->getY()][entity->getX()] = entity->getSymbol();
        }
    }

    // Print the final composed grid
    for (const auto &row : output_grid)
    {
        std::cout << row << "\n";
    }
}

bool Grid::isWall(int x, int y) const
{
    return m_cells[y][x] == '#';
}

int Grid::width() const
{
    return m_cells.empty() ? 0 : static_cast<int>(m_cells[0].size());
}

int Grid::height() const
{
    return static_cast<int>(m_cells.size());
}
