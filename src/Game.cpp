#include "../include/Game.h"
#include <iostream>

// 1) Game ctor: init grid+player, seed RNG, and spawn first monster
Game::Game(int rows, int statusCols)
    : m_grid(rows, statusCols),
      m_player(1, 1, /*playerHP=*/5),
      m_monster(0, 0, /*hp=*/0), // dummy, real spawn happens below
      m_rng(std::random_device{}())
{
    spawnMonster();
}

// 2) Main loop: draw → update → statusCollision → repeat until level complete
void Game::run()
{
    while (!m_levelComplete && !m_gameOver)
    {
        // 1) Clear screen and draw grid with entities
        m_grid.clearScreen();
        drawScene();

        // 2) Draw status info
        std::cout << "HP: " << m_player.getHP() << " | Monster HP: " << m_monster.getHP() << "\n";

        // 3) Get user input and update player
        char command = getPlayerInput();
        m_player.update(command, m_grid);

        // 4) Check for collision and handle it
        if (m_player.collidesWith(m_monster))
        {
            handleCollision();
        }
    }

    // Post-loop screen
    if (m_levelComplete)
    {
        std::cout << "\n🏆 You’ve conquered this dungeon! 🏆\n";
    }
    else if (m_gameOver)
    {
        std::cout << "\n💀 GAME OVER 💀\n";
    }
}

// 3) statusCollision outcome: win, lose, or tie→duel
void Game::handleCollision()
{
    int pHP = m_player.getHP();
    int mHP = m_monster.getHP();

    if (pHP > mHP)
    {
        earnHP();
        std::cout << "🚀 You defeated the tier-" << mHP << " monster!\n";
        std::cin.ignore();
        spawnMonster();
    }
    else if (pHP < mHP)
    {
        std::cout << "💀 You were defeated by the tier-" << mHP << " monster…\n";
        std::cin.ignore();
        m_gameOver = true; // game over
    }
    else
    {
        std::cout << "Equal strength! A special duel begins…\n";
        std::cin.ignore(); // you can later branch into another routine
        handleDuel();
    }
}

// 4) Dice‐roll duel on ties
void Game::handleDuel()
{
    std::cout << "🎲 Rolling dice to decide the duel... 🎲\n";
    while (true)
    {
        int pRoll = getRandomInt(1, 6);
        int mRoll = getRandomInt(1, 6);
        std::cout << "Your roll " << pRoll
                  << " vs. monster's " << mRoll << ".\n";

        if (pRoll > mRoll)
        {
            earnHP();
            std::cout << "🚀 You won the duel! Your HP is now "
                      << m_player.getHP() << ".\n";
            std::cin.ignore();
            spawnMonster(); // a stronger one
            return;         // back to main loop in Game::run()
        }
        else if (pRoll < mRoll)
        {
            std::cout << "💀 You lost the duel…\n";
            std::cin.ignore(); // pause on defeat
            m_gameOver = true; // game over
            return;
        }
        else
        {
            std::cout << "It's a tie! Rerolling…\n\n";
        }
    }
}

// 5) Reward
void Game::earnHP()
{
    int newHP = m_player.getHP() + m_monster.getHP();
    m_player.setHP(newHP);
}

// 6) Encapsulate all monster‐spawn logic & level‐complete check
void Game::spawnMonster()
{

    int playerHP = m_player.getHP();
    std::vector<int> allowed; /*fair combat*/

    // filter tiers
    for (int t : m_tiers)
    {
        if (t >= playerHP && t <= playerHP + 5)
            allowed.push_back(t);
    }

    if (allowed.size() == 1)
    {
        std::cout << "👹 FINAL BATTLE BEGINS!\n\n";
    }

    if (allowed.empty())
    {
        // no fair fight remains → level complete
        m_levelComplete = true; // Breaks the Game::run()'s loop
        return;                 // LEVEL COMPLETE
    }

    // Pick a random HP and interior cell
    int randIndex = getRandomInt(0, allowed.size() - 1);
    int chosenHP = allowed[randIndex];
    int maxX = m_grid.width() - 2;
    int maxY = m_grid.height() - 2;
    int spawnX = getRandomInt(1, maxX);
    int spawnY = getRandomInt(1, maxY);

    // Construct the monster with explicit coords + HP
    m_monster = Monster(spawnX, spawnY, chosenHP);
}

int Game::getRandomInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_rng); //  overloading the function call operator technique.
}

char Game::getPlayerInput() const
{
    char cmd;
    // Prompt until valid input
    while (true)
    {
        std::cout << "Move (w/a/s/d): ";
        std::cin >> cmd;
        cmd = static_cast<char>(std::tolower(cmd));

        if (cmd == 'w' || cmd == 'a' || cmd == 's' || cmd == 'd')
        {
            return cmd;
        }

        std::cout << "Invalid. Use w/a/s/d.\n";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
}

void Game::drawScene() const
{
    for (int y = 0; y < m_grid.height(); ++y)
    {
        for (int x = 0; x < m_grid.width(); ++x)
        {
            // Check for entities at this position first
            if (m_player.getX() == x && m_player.getY() == y)
            {
                std::cout << m_player.getSymbol();
            }
            else if (m_monster.getX() == x && m_monster.getY() == y)
            {
                std::cout << m_monster.getSymbol();
            }
            else
            {
                std::cout << m_grid.getCell(x, y);
            }
        }
        std::cout << "\n";
    }
}