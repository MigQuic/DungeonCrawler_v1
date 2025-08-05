#include "../include/Entity.h"
#include "../include/Grid.h" // for the update() signature

#include <iostream>

// Constructor
Entity::Entity(int x, int y, char sym, int hp) :  // sym was a char
    m_x(x), 
    m_y(y), 
    m_sym(sym),
    m_hp(hp)
{}


// Getters
int Entity::getX() const { return m_x; } 
int Entity::getY() const { return m_y; }
int Entity::getHP() const { return m_hp; }

// Setters
void Entity::setPosition(int x, int y) {
    m_x = x;
    m_y = y;
}

void Entity::setHP(int hp) {
    m_hp = hp;
}