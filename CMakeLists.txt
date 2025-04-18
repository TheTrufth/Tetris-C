cmake_minimum_required(VERSION 3.15)
project(tetris C)

set(CMAKE_C_STANDARD 11)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
# Use vcpkg
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "/Users/student/Documents/tetris-c/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

find_package(SDL2 CONFIG REQUIRED)

add_executable(tetris src/main.c src/game.c src/tetromino.c)
# Link libraries
if (WIN32)
    target_link_libraries(tetris PRIVATE SDL2::SDL2 SDL2::SDL2main)
else()
    target_link_libraries(tetris PRIVATE SDL2::SDL2)
endif()
