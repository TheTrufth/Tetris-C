#include "game.h"

int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};
void game_init()
{
    // (Optional) to intialize game state in the future
}

void game_render(SDL_Renderer *renderer)
{
    // Render the blocks first
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            SDL_Rect cell = {
                x * BLOCK_SIZE,
                y * BLOCK_SIZE,
                BLOCK_SIZE,
                BLOCK_SIZE};
            if (board[y][x])
            {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // Block color
                SDL_RenderFillRect(renderer, &cell);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Gray grid lines
                SDL_RenderDrawRect(renderer, &cell);
            }
        }
    }
}

void place_tetromino(Tetromino *t)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (t->shape[i][j])
            {
                int x = t->x + j;
                int y = t->y + i;

                if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT)
                {
                    board[y][x] = 1; // Can store color index or block presence
                }
            }
        }
    }
}

void clear_lines()
{
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        int full = 1;
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (board[y][x] == 0)
            {
                full = 0;
                break;
            }
        }

        if (full)
        {
            for (int row = y; row > 0; row--)
            {
                for (int x = 0; x < BOARD_WIDTH; x++)
                {
                    board[row][x] = board[row - 1][x];
                }
            }
            // Clear the top row
            for (int x = 0; x < BOARD_WIDTH; x++)
            {
                board[0][x] = 0;
            }
        }
    }
}
