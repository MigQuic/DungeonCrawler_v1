#pragma once
#include "Grid.h"
#include "Player.h"
#include "Monster.h"
#include <random>
#include <optional>
#include <vector>
#include <memory>

class Game
{
public:
    Game(int rows, int cols);
    void run();

private:
    void spawnMonster(); // encapsulates all RNG & filtering
    char getPlayerInput() const;
    void handleCollisions();
    void handleDuel(std::vector<std::unique_ptr<Monster>>::iterator& monster_it);
    void earnHP(const Monster& defeatedMonster);
    void drawScene() const;
    int getRandomInt(int min, int max);

    Grid m_grid;
    Player m_player;
    std::vector<std::unique_ptr<Monster>> m_monsters;
    std::mt19937 m_rng; // Mersenne Twister random engine
    std::vector<int> m_tiers{5, 10, 15, 20, 25, 30, 40};
    bool m_levelComplete = false;
    bool m_gameOver = false;
};
