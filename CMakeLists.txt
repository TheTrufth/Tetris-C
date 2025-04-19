cmake_minimum_required(VERSION 3.15)
project(tetris C)

set(CMAKE_C_STANDARD 11)

# Find packages
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

# Create the executable first
add_executable(tetris src/main.c src/game.c src/tetromino.c)

# Now link the libraries
target_link_libraries(tetris PRIVATE
    SDL2::SDL2
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
)

# Optional SDL2main for Windows
if(WIN32)
    target_link_libraries(tetris PRIVATE SDL2::SDL2main)
endif()
