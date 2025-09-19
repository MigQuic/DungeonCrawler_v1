#include "../include/Game.h"
#include <iostream>
#include <algorithm> // For std::ranges
#include <optional>  // For std::optional

// 1) Game ctor: init grid+player, seed RNG, and spawn first monster
Game::Game(int rows, int cols)
    : m_grid(rows, cols),
      m_player(1, 1, /*playerHP=*/5),
      // m_monster is default-initialized to empty
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

        // 2) Draw status info (only if monster exists)
        std::cout << "HP: " << m_player.getHP();
        if (m_monster) {
            std::cout << " | Monster HP: " << m_monster->getHP();
        }
        std::cout << "\n";

        // 3) Get user input and update player
        char command = getPlayerInput();
        m_player.update(command, m_grid);

        // 4) Check for collision and handle it (only if monster exists)
        if (m_monster && m_player.collidesWith(*m_monster))
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
    int mHP = m_monster->getHP();

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
        int mRoll = getRandomInt(1, 6); // Monster could have its own dice later
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
    int newHP = m_player.getHP() + m_monster->getHP();
    m_player.setHP(newHP);
}

// 6) Encapsulate all monster‐spawn logic & level‐complete check
void Game::spawnMonster()
{

    int playerHP = m_player.getHP();
    std::vector<int> allowedTiers;

    // Use a standard algorithm to filter for allowed tiers (C++11 and later)
    std::copy_if(m_tiers.begin(), m_tiers.end(), std::back_inserter(allowedTiers),
                 [playerHP](int tier) { return tier >= playerHP && tier <= playerHP + 5; });

    if (allowedTiers.size() == 1 && m_tiers.back() == allowedTiers.front())
    {
        std::cout << "👹 FINAL BATTLE BEGINS!\n\n";
    }

    if (allowedTiers.empty())
    {
        // no fair fight remains → level complete
        m_monster.reset(); // Remove the monster from the game
        m_levelComplete = true; // Breaks the Game::run()'s loop
        return;                 // LEVEL COMPLETE
    }

    // Pick a random HP and interior cell
    int randIndex = getRandomInt(0, allowedTiers.size() - 1);
    int chosenHP = allowedTiers[randIndex];
    int maxX = m_grid.width() - 2;
    int maxY = m_grid.height() - 2;
    int spawnX = getRandomInt(1, maxX);
    int spawnY = getRandomInt(1, maxY);

    // Use emplace to construct the monster in-place
    m_monster.emplace(spawnX, spawnY, chosenHP);
}

int Game::getRandomInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_rng); //  overloading the function call operator technique.
}

char Game::getPlayerInput() const
{
    char cmd;
    std::cout << "Move (w/a/s/d): ";
    std::cin >> cmd;

    // Clear any error flags and ignore the rest of the line
    // This makes input handling more robust if the user types "dave" instead of "d"
    if (std::cin.fail()) {
        std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return static_cast<char>(std::tolower(cmd));
}

void Game::drawScene() const
{
    // Collect all drawable entities
    std::vector<const Entity*> entitiesToDraw;
    entitiesToDraw.push_back(&m_player);
    if (m_monster) {
        entitiesToDraw.push_back(&(*m_monster));
    }

    // The grid is now responsible for the actual drawing
    m_grid.draw(entitiesToDraw);
}