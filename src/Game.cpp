#include "../include/Game.h"
#include <iostream>
#include <cstdlib>   // for std::exit, std::rand, std::srand -> General Utilities 
#include <ctime>     // for std::time


// ----- NEW-------------

#include "../include/NCursesUI.h"
#include <string>



// ----------------------

// 1) Game ctor: init grid+player, seed RNG, and spawn first monster
Game::Game(int rows, int cols)
  : m_grid(rows, cols),
    m_player(1, 1, /*playerHP=*/5),
    m_monster(0, 0, /*hp=*/0)  // dummy, real spawn happens below
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    spawnMonster();
}


// 2) Main loop: draw → update → collision → repeat until level complete
void Game::run() {

    NCursesUI ui;           // initscr()/endwin() handled in ctor/dtor

    while (!m_levelComplete) {

        // 1) Clear & draw the static map
        ui.clear();
        // m_grid.clearScreen();            DEPRECATED

        for (int y = 0; y < m_grid.height(); ++y){
            for (int x = 0; x < m_grid.width(); ++x){
                // 1) ask the grid "what char is at (x, y)?"
                char cell = m_grid.getCell(x, y);

                // 2) tell Ncurses to draw that char at screen coords (x, y)
                ui.drawCell(x, y, cell);          
            }
        }

        // 2) Draw player & monster on top
        ui.drawCell(m_player.getX(), m_player.getY(), '@');
        ui.drawCell(m_monster.getX(), m_monster.getY(), 'M');

        // Terminal Output >> DEPERECATED
        // m_grid.draw(
        //     m_player.getX(), m_player.getY(),
        //     m_monster.getX(), m_monster.getY()
        // );


        // 3) Draw HP/status on the right
        int col = m_grid.width() + 2;
        ui.drawText(0, col, ("HP:    " + std::to_string(m_player.getHP())).c_str());
        ui.drawText(1, col, ("Level: " + std::to_string(1 /* or world */)).c_str());

        ui.refresh();

        // 4) Read exactly one key
        int ch = ui.getKey();

        // 5) Map key to a delta
        int dx = 0, dy = 0;
        if          (ch == 'w' || ch == KEY_UP) dy = -1;
        else if     (ch == 's' || ch == KEY_DOWN) dy = 1;
        else if     (ch == 'a' || ch == KEY_LEFT) dx = -1; 
        else if     (ch == 'd' || ch == KEY_RIGHT) dx = 1; 
        else continue;          // ignore any other key


        // 6) Attempt move (check walls)
        int nx = m_player.getX() + dx;
        int ny = m_player.getY() + dy;
        if(!m_grid.isWall(nx, ny)){
            m_player.setPosition(nx, ny);       // Comes from Entity::setPosition()
        }


        // DEPRECATED: it used to move the player and respawn a monster
        // m_player.update(m_grid);
        // m_monster.update(m_grid);

        // 7) Inmediate collision test
        if (m_player.collidesWith(m_monster)) {
            handleCollision();
        }
    }

    // Level-complete splash
    ui.clear();
    ui.drawText(0, 0, "🏆 You’ve conquered this dungeon! 🏆")
    ui.refresh();
    ui.getKey();        // wait for any key before exiting


    // std::cout << "\n🏆 You’ve conquered this dungeon! 🏆\n";   // DEPRECATED: console-print
}


// 3) Collision outcome: win, lose, or tie→duel
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
        std::exit(0);             // game over
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
            std::exit(0);           // game over
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
        if (t >= playerHP && t <= playerHP + 5) // playerHP * 2 instead?
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