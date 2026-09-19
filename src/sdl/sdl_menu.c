#include <SDL2/SDL.h>
#include <stdbool.h>

#include "ui_and_engine.h"
#include "manager.h"

void process_menu_input(Game_t *game)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            game->running = false;
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                game->running = false;
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
            {
                game->game_state = GAME;
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_T)
            {
                game->wraparound ^= 1;
            }
        }
    }
}
