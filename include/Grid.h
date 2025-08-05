#pragma once
#include <string>
#include <vector>

class Grid {
    public:
        Grid(int rows, int cols);

        // Clears the console (crude) then re-draws the map
        void clearScreen() const;

        // it also draws the player and monster
        void draw(int px, int py, int mx, int my) const;
        bool isWall(int x, int y) const;

        // Game needs to ask the Grid for the size of m_cells
        int width()  const;
        int height() const;
        char getCell(int x, int y) const;

    private:
    std::vector<std::string> m_cells;
};
