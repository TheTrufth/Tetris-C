#include "game.h"

void game_init()
{
    // (Optional) to intialize game state in the future
}

void game_render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Gray grid lines

    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            SDL_Rect cell = {
                x * BLOCK_SIZE,
                y * BLOCK_SIZE,
                BLOCK_SIZE,
                BLOCK_SIZE};
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}