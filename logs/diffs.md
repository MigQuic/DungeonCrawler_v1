diff --git a/.gitignore b/.gitignore
index 20b4280..8925da7 100644
--- a/.gitignore
+++ b/.gitignore
@@ -5,4 +5,7 @@
 DungeonCrawler_v1
 
 # Ignore compiled object files
-*.o
\ No newline at end of file
+*.o
+
+# Ignore my notes these are just for me
+/Notes
\ No newline at end of file
diff --git a/README/ProjectOverview.txt b/README/ProjectOverview.txt
deleted file mode 100644
index 194b03e..0000000
--- a/README/ProjectOverview.txt
+++ /dev/null
@@ -1,48 +0,0 @@
-PROJECT OVERVIEW:
-
-DungeonCrawler is a text‑based console game where you:
-    1. See a dungeon map with you as '@' and monsters as 'C' or 'L'.
-    2. Move with w/a/s/d to explore.
-    3. Encounter monsters, which triggers combat based on HP.
-    4. Defeat monsters to gain their HP and face stronger foes.
-
-Milestones (Levels 1–5)
-    [✓] LEVEL 1: Grid generates and prints; player can move '@' inside walls.
-    [✓] LEVEL 2: Monsters spawn; collision triggers an encounter.
-    [✓] LEVEL 3: HP system implemented; combat decided by HP comparison. A dice-roll duel occurs on a tie.
-    [✓] LEVEL 4: Code refactored into a clean class hierarchy (Entity, Player, Monster, etc.).
-    [ ] LEVEL 5: (Future) Add more features like inventory, items, more monster types, and saving/loading the game.
-
-Design summary
-================
-Class Hierarchy
----------------
-The project uses an object-oriented design:
-- Entity: The base for anything with a position, symbol, and HP.
-  - Player: The user-controlled '@'.
-  - Monster: An abstract base for enemies.
-    - ChaserMonster ('C'): AI chases the player.
-    - LooterMonster ('L'): AI flees from the player.
-
-Monster Tiers
--------------
-The player starts with 5 HP. Monsters spawn with HP from a list of tiers {5, 10, 15, 20, 25, 30, 40}.
-The game spawns monsters with HP in a range related to the player's current HP, ensuring a fair challenge.
-When all beatable monster tiers are exhausted, the level is complete.
-
-Collision outcome
------------------
-When the player and a monster occupy the same cell:
-1. Player HP > Monster HP:
-   - The monster is defeated.
-   - The player's HP increases by the monster's HP.
-   - A new monster spawns.
-2. Player HP < Monster HP:
-   - The player is defeated.
-   - Game Over.
-3. Player HP == Monster HP:
-   - A "Duel" begins!
-   - Player and monster roll a 6-sided die.
-   - The higher roll wins the duel. A tie results in a reroll.
-   - Winning the duel has the same outcome as (1).
-   - Losing the duel has the same outcome as (2).
diff --git a/README/skeleton.txt b/README/skeleton.txt
deleted file mode 100644
index 39628e4..0000000
--- a/README/skeleton.txt
+++ /dev/null
@@ -1,19 +0,0 @@
-.
-├── include/
-│   ├── Entity.h        # Base class for all game objects (Player, Monster)
-│   ├── Player.h        # The user-controlled character '@'
-│   ├── Monster.h       # Abstract base class for all monsters
-│   ├── ChaserMonster.h # A monster 'C' that chases the player
-│   ├── LooterMonster.h # A monster 'L' that flees from the player
-│   ├── Grid.h          # The game map, handles drawing
-│   └── Game.h          # The main game engine, orchestrates everything
-├── src/
-│   ├── main.cpp        # Entry-point: constructs Game and calls run()
-│   ├── Entity.cpp      # Implementation for Entity
-│   ├── Player.cpp      # Implementation for Player
-│   ├── Monster.cpp     # Shared "template method" for monster updates
-│   ├── ChaserMonster.cpp # AI logic for ChaserMonster
-│   ├── LooterMonster.cpp # AI logic for LooterMonster
-│   ├── Grid.cpp        # Grid's implementation (map generation & drawing)
-│   └── Game.cpp        # Game's implementation (main loop, rules, state)
-└── CMakeLists.txt      # Build script for CMake
