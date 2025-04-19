#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include "game.h"
#include "tetromino.h"
#include <SDL_ttf.h>

#define WINDOW_WIDTH ((BOARD_WIDTH + 6) * BLOCK_SIZE) // Extra 6 blocks wide
#define WINDOW_HEIGHT (BOARD_HEIGHT * BLOCK_SIZE)

Tetromino currentTetromino;
Tetromino nextTetromino;
int score = 0;

void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y)
{
    SDL_Color color = {255, 255, 255, 255}; // White text
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void hard_drop(Tetromino *t)
{
    while (can_move(t, 0, 1))
    {
        t->y += 1;
    }

    // Place the tetromino into the board and reset
    place_tetromino(t);
    clear_lines(&score);            // If you’ve implemented this
    *t = nextTetromino;             // Move to the next tetromino
    tetromino_init(&nextTetromino); // Initialize the next tetromino
}

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

                if (newX < 0 || newX >= BOARD_WIDTH || newY < 0 || newY >= BOARD_HEIGHT || board[newY][newX])
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
    srand(time(NULL)); // Seed the random number generator
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Load the font
    TTF_Font *font = TTF_OpenFont("src/assets/fonts/Beckett.ttf", 24);
    if (!font)
    {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
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

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Enable alpha blending.
    game_init();
    // Intialise tetromino
    tetromino_init(&currentTetromino);
    tetromino_init(&nextTetromino);

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
                    break;
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
                case SDLK_SPACE:
                    hard_drop(&currentTetromino);
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
            else
            {
                // Place the tetromino on the board
                place_tetromino(&currentTetromino);
                // Clear lines
                clear_lines(&score);
                // Reset tetromino
                tetromino_init(&currentTetromino);
            }
            lastTick = currentTick;
        }

        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        game_render(renderer);

        // 👻 Draw ghost first so it's behind the active tetromino
        tetromino_render_ghost(&currentTetromino, renderer);

        // 🧱 Then draw actual piece
        tetromino_render(&currentTetromino, renderer);

        // 🖼️ Draw preview of next piece
        SDL_Rect previewBox = {
            BOARD_WIDTH * BLOCK_SIZE + 32,
            64,
            4 * BLOCK_SIZE,
            4 * BLOCK_SIZE};
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderDrawRect(renderer, &previewBox);

        char scoreText[64];
        sprintf(scoreText, "Score: %d", score);
        render_text(renderer, font, scoreText, BOARD_WIDTH * BLOCK_SIZE + 32, 16);
        render_text(renderer, font, "NEXT", BOARD_WIDTH * BLOCK_SIZE + 64, 45);

        int previewX = BOARD_WIDTH * BLOCK_SIZE + 32; // right after the board
        int previewY = 64;                            // Offset for preview
        tetromino_render_preview(&nextTetromino, renderer, previewX, previewY);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Destroy SDL objs and quit SDL system
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_CloseFont(font);
    TTF_Quit();

    return 0;
}