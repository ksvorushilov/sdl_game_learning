#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>

#include "const.h"
#include "font.h"
#include "snake.h"
#include "types.h"
#include "manager.h"

void sdl_cleanup(Game *game) // graceful shutdown.
{
    SDL_ShowCursor(SDL_ENABLE); // show system mouse cursor
    destroy_alphabet();
    destroy_snake(game->snake);
    SDL_DestroyRenderer(game->renderer); 
    SDL_DestroyWindow(game->window);     
    SDL_Quit();       
}

bool sdl_initialise(Game *game)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) // init, returns 0 on success, -1 on failure.
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError()); // gets error message from SDL.
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"); // 0 - nearest, no blur
    game->window = SDL_CreateWindow(WINDOW_TITLE,
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT,
                                    0); // create window, returns pointer to window on success, NULL on failure.
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
    SDL_ShowCursor(SDL_DISABLE); // hide system mouse cursor
    return true;
}