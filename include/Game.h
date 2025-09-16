#pragma once
#include "Grid.h"
#include "Player.h"
#include "Monster.h"
#include <vector>

class Game {
public:
    Game(int rows, int cols);
    void run();

private:
    void spawnMonster();            // encapsulates all RNG & filtering
    void handleCollision();
    void handleDuel();
    void earnHP();                  // after a won duel

    Grid            m_grid;
    Player          m_player;
    Monster         m_monster;      // must be initialized explicitly
    std::vector<int> m_tiers{5, 10, 15, 20, 25, 30, 40};
    bool            m_levelComplete = false;
    bool            m_gameOver = false;
};
