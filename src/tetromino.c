#include "tetromino.h"
#include <stdlib.h>
#include <time.h>
#include "game.h"

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

void tetromino_render_ghost(Tetromino *tetromino, SDL_Renderer *renderer)
{
    // Copy the tetromino so we can move it
    Tetromino ghost = *tetromino;

    // Move down until it would collide
    while (can_move(&ghost, 0, 1))
    {
        ghost.y += 1;
    }

    // Render with lower alpha (transparency)
    SDL_Color ghostColor = ghost.color;
    ghostColor.a = 100; // make it translucent

    SDL_SetRenderDrawColor(renderer, ghostColor.r, ghostColor.g, ghostColor.b, ghostColor.a);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (ghost.shape[i][j])
            {
                SDL_Rect block = {
                    (ghost.x + j) * BLOCK_SIZE,
                    (ghost.y + i) * BLOCK_SIZE,
                    BLOCK_SIZE,
                    BLOCK_SIZE};
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
}

void tetromino_render_preview(Tetromino *tetromino, SDL_Renderer *renderer, int offsetX, int offsetY)
{
    int minX = 4, maxX = 0, minY = 4, maxY = 0;

    // Find bounds of active blocks
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tetromino->shape[i][j])
            {
                if (j < minX)
                    minX = j;
                if (j > maxX)
                    maxX = j;
                if (i < minY)
                    minY = i;
                if (i > maxY)
                    maxY = i;
            }
        }
    }

    int shapeWidth = (maxX - minX + 1) * BLOCK_SIZE;
    int shapeHeight = (maxY - minY + 1) * BLOCK_SIZE;

    int centerOffsetX = (4 * BLOCK_SIZE - shapeWidth) / 2;
    int centerOffsetY = (4 * BLOCK_SIZE - shapeHeight) / 2;

    SDL_SetRenderDrawColor(renderer, tetromino->color.r, tetromino->color.g, tetromino->color.b, 80);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tetromino->shape[i][j])
            {
                SDL_Rect block = {
                    offsetX + centerOffsetX + (j - minX) * BLOCK_SIZE,
                    offsetY + centerOffsetY + (i - minY) * BLOCK_SIZE,
                    BLOCK_SIZE,
                    BLOCK_SIZE};
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
}
