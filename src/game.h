#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "tetromino.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define BLOCK_SIZE 32

void game_init();
void game_render(SDL_Renderer *renderer);
extern int board[BOARD_HEIGHT][BOARD_WIDTH];
void place_tetromino(Tetromino *t);
void clear_lines();
#endif