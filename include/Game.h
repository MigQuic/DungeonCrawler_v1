#pragma once
#include "Grid.h"
#include "Player.h"
#include "Monster.h"
#include <random>
#include <optional>
#include <vector>

class Game
{
public:
    Game(int rows, int cols);
    void run();

private:
    void spawnMonster(); // encapsulates all RNG & filtering
    char getPlayerInput() const;
    void handleCollision();
    void handleDuel();
    void earnHP(); // after a won duel
    void drawScene() const;
    int getRandomInt(int min, int max);

    Grid m_grid;
    Player m_player;
    std::optional<Monster> m_monster;
    std::mt19937 m_rng; // Mersenne Twister random engine
    std::vector<int> m_tiers{5, 10, 15, 20, 25, 30, 40};
    bool m_levelComplete = false;
    bool m_gameOver = false;
};
