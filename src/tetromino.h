#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL.h>
#define BLOCK_SIZE 32

typedef struct
{
    int x, y;        // Position of the tetromino on the grid
    int shape[4][4]; // A 4x4 matrix to store the shape (each element is a block)
    SDL_Color color; // Color of the tetromino
} Tetromino;

void tetromino_init(Tetromino *tetromino);
void tetromino_render(Tetromino *tetromnino, SDL_Renderer *renderer);
void rotate_tetromino(Tetromino *t);
void tetromino_render_ghost(Tetromino *tetromino, SDL_Renderer *renderer);
#endif