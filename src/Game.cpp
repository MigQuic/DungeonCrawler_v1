#include "../include/Game.h"
#include <iostream>
#include <cstdlib>   // for std::exit, std::rand, std::srand -> General Utilities 
#include <ctime>     // for std::time



// 1) Game ctor: init grid+player, seed RNG, and spawn first monster
Game::Game(int rows, int statusCols)
  : m_grid(rows, statusCols),
    m_player(1, 1, /*playerHP=*/5),
    m_monster(0, 0, /*hp=*/0)  // dummy, real spawn happens below
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    spawnMonster();
}


// 2) Main loop: draw → update → statusCollision → repeat until level complete
void Game::run() {
    while (!m_levelComplete && !m_gameOver) {
        // 1) Clear screen and draw grid with entities
        m_grid.clearScreen();
        m_grid.draw(m_player.getX(), m_player.getY(), m_monster.getX(), m_monster.getY());
        
        // 2) Draw status info
        std::cout << "HP: " << m_player.getHP() << " | Monster HP: " << m_monster.getHP() << "\n";
        
        // 3) Delegate input and movement to Player
        m_player.update(0, m_grid); // Pass a dummy command; Player handles its own input
        
        // 4) Check for collision and handle it
        if (m_player.collidesWith(m_monster)) {
            handleCollision();
        }
    }

    // Post-loop screen
    if (m_levelComplete) {
        std::cout << "\n🏆 You’ve conquered this dungeon! 🏆\n";
    } else if (m_gameOver) {
        std::cout << "\n💀 GAME OVER 💀\n";
    }
}


// 3) statusCollision outcome: win, lose, or tie→duel
void Game::handleCollision() {
    int pHP = m_player.getHP();
    int mHP = m_monster.getHP();

    if (pHP > mHP) {
        earnHP();
        std::cout << "🚀 You defeated the tier-" << mHP << " monster!\n";
        std::cin.ignore();
        spawnMonster();
    }
    else if (pHP < mHP) {
        std::cout << "💀 You were defeated by the tier-" << mHP << " monster…\n";
        std::cin.ignore();  
        m_gameOver = true;        // game over
    }
    else {
        std::cout << "Equal strength! A special duel begins…\n";
        std::cin.ignore();        // you can later branch into another routine
        handleDuel();
    }
}


// 4) Dice‐roll duel on ties
void Game::handleDuel() {
    std::cout << "🎲 Rolling dice to decide the duel... 🎲\n";
    while (true) {
        int pRoll = std::rand() % 6 + 1;
        int mRoll = std::rand() % 6 + 1;
        std::cout << "Your roll " << pRoll
                  << " vs. monster's " << mRoll << ".\n";

        if (pRoll > mRoll) {
            earnHP();
            std::cout << "🚀 You won the duel! Your HP is now "
                      << m_player.getHP() << ".\n";
            std::cin.ignore();
            spawnMonster();         // a stronger one 
            return;                 // back to main loop in Game::run()
        }
        else if (pRoll < mRoll) {
            std::cout << "💀 You lost the duel…\n";
            std::cin.ignore();      // pause on defeat
            m_gameOver = true;      // game over
            return;
        }
        else {
            std::cout << "It's a tie! Rerolling…\n\n";
        }
    }
}


// 5) Reward 
void Game::earnHP() {
    int newHP = m_player.getHP() + m_monster.getHP();
    m_player.setHP(newHP);
}


// 6) Encapsulate all monster‐spawn logic & level‐complete check
void Game::spawnMonster(){

  int playerHP = m_player.getHP();
  std::vector<int> allowed; /*fair combat*/

  // filter tiers
  for (int t : m_tiers) {
        if (t >= playerHP && t <= playerHP + 5) 
            allowed.push_back(t);
  }

  if (allowed.size() == 1) {
    std::cout << "👹 FINAL BATTLE BEGINS!\n\n";
  }

  if (allowed.empty()){
    // no fair fight remains → level complete
    m_levelComplete = true;       // Breaks the Game::run()'s loop
    return;                       // LEVEL COMPLETE
  }

  // Pick a random HP and interior cell
  int chosenHP = allowed[std::rand() % allowed.size()];
  int maxX     = m_grid.width()  - 2;
  int maxY     = m_grid.height() - 2;
  int spawnX   = (std::rand() % maxX) + 1;
  int spawnY   = (std::rand() % maxY) + 1;


  // Construct the monster with explicit coords + HP
  m_monster = Monster(spawnX, spawnY, chosenHP);
}