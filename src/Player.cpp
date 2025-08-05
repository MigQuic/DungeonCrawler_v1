#include "../include/Player.h"
#include "../include/Grid.h"
#include <iostream>
#include <cctype>

using std::cout;
using std::cin;

Player::Player(int x, int y, int hp) : 
    Entity(x, y, '@', hp) 
{}

// -------------------------------------------------

void Player::update(const Grid& grid){
    char cmd;
    
    // Prompt until valid input
    while (true){
        cout << "Move (w/a/s/d): ";
        cin >> cmd;
        cmd = static_cast<char>(std::tolower(cmd));

        if (cmd == 'w' || cmd == 'a' || cmd == 's' || cmd == 'd'){
            break;
        }

        cout << "Invalid. Use w/a/s/d.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // Compute delta -> d: direction
    int dx = 0, dy = 0;
    switch(cmd) {
        case 'w' : dy = -1; break;
        case 's' : dy = 1; break;
        case 'a' : dx = -1; break;
        case 'd' : dx = 1; break;
    }

    // Attempt move
    int newX = m_x + dx;
    int newY = m_y + dy;

    if (!grid.isWall(newX, newY)){
        m_x = newX;
        m_y = newY;
    }
}
