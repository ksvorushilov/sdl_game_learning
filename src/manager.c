#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "snake.h"
#include "types.h"
#include "manager.h"
#include "ui_and_engine.h"


void game_cleanup(Game_t *game) // graceful shutdown.
{
    // destroy_alphabet();
    destroy_snake(game->snake);
    engine_destroy_renderer(game->renderer);
    engine_destroy_window(game->window);
    engine_quit();
}

bool game_initialise(Game_t *game)
{
    if (engine_init() != EXIT_SUCCESS) // init, returns 0 on success, -1 on failure.
    {
        fprintf(stderr, "Game Engine Error.\n");
        return false;
    }
    game->window = engine_create_window(FIELD_WIDTH, FIELD_HEIGHT);
    if ((game->window.window) == NULL)
    {
        fprintf(stderr, "Error creating window.\n");
        return false;
    };
    game->renderer = engine_create_renderer(game->window);
    if ((game->renderer.renderer) == NULL)
    {
        fprintf(stderr, "Error creating renderer\n");
        return false;
    }

    return true;
}
