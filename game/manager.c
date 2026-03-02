#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>

#include "const.h"
#include "font.h"
#include "types.h"
#include "manager.h"

void sdl_cleanup(struct Game *game, int exit_status) // graceful shutdown.
{
    destroy_alphabet();
    SDL_DestroyRenderer(game->renderer); // is able to process NULL, so no prior check required
    SDL_DestroyWindow(game->window);     // same thing as previous line
    SDL_Quit();                          // void SDL_Quit(void), cleans up all allocated memory by SDL
    exit(exit_status);
}

bool sdl_initialise(struct Game *game)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) // init, returns 0 on success, -1 on failure.
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError()); // gets error message from SDL.
        return false;
    }
    game->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0); // create window, returns pointer to window on success, NULL on failure.
    if (game->window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return false;
    }
    game->renderer = SDL_CreateRenderer(game->window, -1, 0);
    if (game->renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}