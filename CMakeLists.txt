cmake_minimum_required(VERSION 3.10)

# Project name → matches your executable and version tag
project(DungeonCrawler_v1 VERSION 1.0 LANGUAGES CXX)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1) Your headers live under include/
include_directories(${PROJECT_SOURCE_DIR}/include)

# 2) Find & include ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

# 3) Build the executable from your .cpp files
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Grid.cpp
    src/Entity.cpp
    src/Player.cpp
    src/Monster.cpp
    src/Game.cpp
    src/NCursesUI.cpp
)

# 4) Link against ncurses
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES})

