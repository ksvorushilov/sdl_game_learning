#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#include "ui_and_engine.h"
#include "manager.h"

#include "sdl_bindings.h"

void process_game_input(Game_t *game)
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
            action_enum_t action = key_match(event.key.keysym.scancode, BIND_GAME);
            if (action == ACTION_UP)
            {
                game->snake_vel_state = UP;
            }
            if (action == ACTION_LEFT)
            {
                game->snake_vel_state = LEFT;
            }
            if (action == ACTION_DOWN)
            {
                game->snake_vel_state = DOWN;
            }
            if (action == ACTION_RIGHT)
            {
                game->snake_vel_state = RIGHT;
            }
        }
    }
}
