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

# Screenshots and Videos

<table>
  <tr>
    <td align="center">
      <img width="300" alt="Screenshot 2025-04-19 at 17 35 47" src="https://github.com/user-attachments/assets/a159b87b-6c2a-44ba-ad14-27963ca26ad4" />
      <br>
      Caption for the first image
    </td>
    <td align="center">
      <img width="300" alt="Screenshot 2025-04-19 at 17 35 52" src="https://github.com/user-attachments/assets/d0c95737-79f2-4ec1-a07e-96aff2ee88e8" />
      <br>
      Caption for the second image
    </td>
    <td align="center">
      <img width="300" alt="Screenshot 2025-04-19 at 17 35 55" src="https://github.com/user-attachments/assets/28017243-fb29-4ed2-9b98-8135d64d693b" />
      <br>
      Caption for the third image
    </td>
  </tr>
</table>

<br>

<!-- Video -->
https://github.com/user-attachments/assets/9ff2bafb-e226-482d-a96e-80bda63c1ec9

# Troubleshooting
Be sure to open any issues up. 
