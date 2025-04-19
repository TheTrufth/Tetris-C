# Tetris Game

# Build Instructions

1. Clone and Bootstrap `vcpkg`
    ```
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.sh   # or bootstrap-vcpkg.bat on Windows
    ```
2. Install `SDL2`
    ```
    ./vcpkg install sdl2
    ```
3. For audio, fonts etc.
    ```./vcpkg install sdl2-image sdl2-mixer sdl2-ttf```
4. Integrate with your compiler (one time)
   ```./vcpkg integrate install```
5. Change dir in `CMakeLists.txt`
6. Build the project
   ```
    mkdir build && cd build
    cmake ..
    cmake --build .
   ```
# Run the game
To run the game `./tetris`

# Controls
- UP, LEFT, RIGHT, DOWN to move the tetromino
- P to pause
- Q to quit
- G to turn on Ghost Preview
- H to show the next tetromino preview
- space to hard drop