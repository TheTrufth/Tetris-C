#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include "game.h"
#include "tetromino.h"

#define WINDOW_WIDTH (BOARD_WIDTH * BLOCK_SIZE)
#define WINDOW_HEIGHT (BOARD_HEIGHT * BLOCK_SIZE)
int can_move(Tetromino *t, int dx, int dy)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (t->shape[i][j])
            {
                int newX = t->x + j + dx;
                int newY = t->y + i + dy;

                if (newX < 0 || newX >= BOARD_WIDTH || newY < 0 || newY >= BOARD_HEIGHT)
                {
                    return 0; // Invalid move
                }
            }
        }
    }
    return 1; // Valid move
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create the window
    SDL_Window *window = SDL_CreateWindow("Tetris",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    game_init();
    // Intialise tetromino
    Tetromino currentTetromino;
    tetromino_init(&currentTetromino);

    int running = 1;
    SDL_Event event;

    Uint32 lastTick = SDL_GetTicks();
    const Uint32 gravityDelay = 500;

    while (running)
    {
        // Poll events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_q:
                    running = 0;
                case SDLK_UP:
                {
                    // Save a copy of the original shape
                    Tetromino temp = currentTetromino;
                    rotate_tetromino(&currentTetromino);
                    if (!can_move(&currentTetromino, 0, 0))
                    {
                        // If rotated shape is invalid, revert to original
                        currentTetromino = temp;
                    }
                    break;
                }
                case SDLK_LEFT:
                    if (can_move(&currentTetromino, -1, 0))
                    {
                        currentTetromino.x -= 1;
                    }
                    break;
                case SDLK_RIGHT:
                    if (can_move(&currentTetromino, 1, 0))
                    {
                        currentTetromino.x += 1;
                    }
                    break;
                case SDLK_DOWN:
                    if (can_move(&currentTetromino, 0, 1))
                    {
                        currentTetromino.y += 1;
                    }
                    break;
                }
            }
        }

        // Gravity: move tetromino down every few milliseconds
        Uint32 currentTick = SDL_GetTicks();
        if (currentTick - lastTick >= gravityDelay)
        {
            if (can_move(&currentTetromino, 0, 1))
            {
                currentTetromino.y += 1;
            }
            lastTick = currentTick;
        }

        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        game_render(renderer);
        tetromino_render(&currentTetromino, renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Destroy SDL objs and quit SDL system
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}