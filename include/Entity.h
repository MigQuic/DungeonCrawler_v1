#pragma once

// forward‐declare, since we'll pass it into update()
// (so we don’t need to include Grid.h here)
class Grid;

class Entity{
    public:
        // // Initialize position (x,y), display symbol (sym) and starting HP
        Entity(int x, int y, char sym, int hp);  // sym was a char
        virtual ~Entity() = default;

        // Provide a default empty implementation.
        // Subclasses like Player can override it. Others can just inherit the empty version.
        virtual void update([[maybe_unused]] char command, [[maybe_unused]] const Grid& grid) { /* Default: do nothing */ }

        bool collidesWith(const Entity& other) const {
            return m_x == other.m_x && m_y == other.m_y;
        }

        // Accesors for position
        int getX() const;
        int getY() const;    
        int getHP() const;
        char getSymbol() const;

        // Setters
        void setPosition(int x, int y);
        void setHP(int hp);

    protected:

        int m_x, m_y;       // position
        char m_sym;         // display symbol
        int m_hp;           // hit points
};
