#include "../include/Grid.h"
#include <iostream>


Grid::Grid(int rows, int cols) {
    std::string border(cols, '#');
    m_cells.push_back(border);

    std::string middle = "#" + std::string(cols - 2, '.') + "#";
    for (int i = 0; i < rows - 2; ++i)
        m_cells.push_back(middle);

    m_cells.push_back(border);
}

void Grid::clearScreen() const {
    // shrink the gap or swap for ANSI escape if you like
    std::cout << std::string(4, '\n');
}


void Grid::draw(int px, int py, int mx, int my) const {
    
    for (int y = 0; y < (int)m_cells.size(); ++y) {
        for (int x = 0; x < (int)m_cells[y].size(); ++x) {
            if      (x == px && y == py)      std::cout << '@';
            else if (x == mx && y == my)      std::cout << 'M';
            else                              std::cout << m_cells[y][x];
        }
        std::cout << "\n";
    }
}


bool Grid::isWall(int x, int y) const {
    return m_cells[y][x] == '#';
}



/* 
These two methods are just helpers so Game can ask the Grid “how big am I?” 
when it needs to, for example, pick a random spawn cell. 
*/

int Grid::width() const {           // defensive programming
    return m_cells.empty() ? 0 
    : static_cast<int>(m_cells[0].size());
}

int Grid::height() const {
    return static_cast<int>(m_cells.size());
}

char Grid::getCell(int x, int y) const {
    return m_cells[x][y];
}
