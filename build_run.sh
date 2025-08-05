#!/usr/bin/env bash

clear

# Set output executable name
OUTPUT=dungeon_crawler

# Compile all .cpp files in src/, add “include/” to your header search path
g++ -std=c++20 -Wall -Wextra -Iinclude \
    -o $OUTPUT \
    src/*.cpp \
    -lncurses

# If compilation succeeded, run the program
if [ $? -eq 0 ]; then
    echo "Build succeeded. Running $OUTPUT..."
    ./$OUTPUT
else
    echo "Build failed."
fi

