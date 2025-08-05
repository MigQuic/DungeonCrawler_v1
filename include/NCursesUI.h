#pragma once
#include <ncurses.h>

class NCursesUI {
    NCursesUI();     // sets up ncurses
    ~NCursesUI();    // tears it down

    void clear();
    void refresh();
    int getKey();


    // draw a single character at (x,y) in your grid
    void drawCell(int x, int y, char ch);

    // draw a text string at absolute screen coords
    void drawText(int row, int col, const char* s);
};