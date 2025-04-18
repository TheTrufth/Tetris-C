#include "tetromino.h"
#include <stdlib.h>
#include <time.h>

void tetromino_init(Tetromino *tetromino)
{
    // Define the 7 types of tetrominoes as 4x4 shapes
    int shapes[7][4][4] = {
        {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // I
        {{1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // T
        {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // O
        {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // S
        {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // Z
        {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // L
        {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}  // J
    };

    // Set random number gen
    srand(time(NULL));

    // Randomly select a shape
    int shapeIndex = rand() % 7;

    // Copy the shape into a tetromino object
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tetromino->shape[i][j] = shapes[shapeIndex][i][j];
        }
    }

    // Set a random color for the tetromino
    tetromino->color.r = rand() % 256;
    tetromino->color.g = rand() % 256;
    tetromino->color.b = rand() % 256;
    tetromino->color.a = 255;

    // Set the initial postion (spawn point)
    tetromino->x = 4; // Start at the middle of the grid
    tetromino->y = 0; // Start at the top
}

void tetromino_render(Tetromino *tetromino, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, tetromino->color.r, tetromino->color.g, tetromino->color.b, tetromino->color.a);

    // Loop through the shape matrix
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tetromino->shape[i][j] != 0)
            {
                SDL_Rect block = {
                    (tetromino->x + j) * BLOCK_SIZE,
                    (tetromino->y + i) * BLOCK_SIZE,
                    BLOCK_SIZE, BLOCK_SIZE};
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
}

void rotate_tetromino(Tetromino *t)
{
    int rotated[4][4] = {0};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // Rotate 90 deg clockwise
            rotated[j][3 - i] = t->shape[i][j];
        }
    }

    // Copy back to original shape
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            t->shape[i][j] = rotated[i][j];
        }
    }
}
