#include "../include/Player.h"
#include "../include/Grid.h"
#include <iostream>
#include <cctype>


Player::Player(int x, int y, int hp) : 
    Entity(x, y, '@', hp) 
{}

// -------------------------------------------------

void Player::update(int /*command*/, const Grid& grid) {
    
    char cmd;
    // Prompt until valid input
    while (true){
        std::cout << "Move (w/a/s/d): ";
        std::cin >> cmd;
        cmd = static_cast<char>(std::tolower(cmd));

        if (cmd == 'w' || cmd == 'a' || cmd == 's' || cmd == 'd'){
            break;
        }

        std::cout << "Invalid. Use w/a/s/d.\n";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }


    // 1) Compute delta 
    int dx = 0, dy = 0;
    switch(cmd) {
        case 'w' : dy = -1; break;
        case 's' : dy = 1; break;
        case 'a' : dx = -1; break;
        case 'd' : dx = 1; break;
        default : return;                        // ignore unrecognized keys
    }

    // 2) Attempt move
    int newX = m_x + dx, newY = m_y + dy;
    if (!grid.isWall(newX, newY)){
        m_x = newX;
        m_y = newY;
    }
}
