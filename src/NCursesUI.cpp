#include "../include/NCursesUI.h"

NCursesUI::NCursesUI() {
    initscr();                  // initialize screen
    cbreak();                   // disable line buffering
    noecho();                   // don’t echo keypresses
    keypad(stdscr, TRUE);       // enable arrow keys, etc.
    curs_set(0);                // hide the cursor
}

NCursesUI::~NCursesUI() {
    endwin();       // restore terminal
}

// --------------------------

void NCursesUI::clear() {
    ::clear();
}

void NCursesUI::refresh() {
    ::refresh();
}

int NCursesUI::getKey() {
    return getch();
}

// --------------------------

void NCursesUI::drawCell(int x, int y, char ch) {
    mvaddch(y, x, ch);
}

void NCursesUI::drawText(int row, int col, const char* s) {
    mvprintw(row, col, "%s", s);
}
