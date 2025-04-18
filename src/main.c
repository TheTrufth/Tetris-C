#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include "game.h"

#define WINDOW_WIDTH (BOARD_WIDTH * BLOCK_SIZE)
#define WINDOW_HEIGHT (BOARD_HEIGHT * BLOCK_SIZE)

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

    int running = 1;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        // Set the drawing color to black (0,0,0) with full opacity (255)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        game_render(renderer);

        SDL_RenderPresent(renderer);
        // Sleep for 16ms -> ~ 60 FPS
        SDL_Delay(16);
    }

    // Destroy SDL objs and quit SDL system
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
