#!/usr/bin/env bash

clear

# The name of the executable as defined in CMakeLists.txt
PROJECT_NAME="DungeonCrawler_v1"

# 1. Create a build directory and navigate into it
mkdir -p build
cd build

# 2. Configure the project with CMake
cmake ..

# 3. Build the project with make
make

# 4. If compilation succeeded, run the program
if [ $? -eq 0 ]; then
    echo "Build succeeded. Running ${PROJECT_NAME}..."
    ./${PROJECT_NAME}
else
    echo "Build failed."
fi
