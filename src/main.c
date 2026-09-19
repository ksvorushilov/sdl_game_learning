#include <stdio.h>
#include <stdlib.h> // EXIT_FAILURE and EXIT_SUCCESS
#include <stdbool.h>

#include "const.h"
#include "game_loop.h"
#include "manager.h"
#include "menu_loop.h"
#include "snake.h"
#include "types.h" // point_2d
#include "ui_and_engine.h"

void input(Game_t *game);
void update(Game_t *game);
void render(Game_t *game);

int main(void)
{
    struct Game_t game = {0}; // initialize struct with null pointers is recommended to avoid undefined behavior when accessing uninitialized pointers.
    if (!game_initialise(&game))
    {
        game_cleanup(&game); // the program is terminated immediately here
        return (EXIT_FAILURE);
    }

    game.running = true;
    platform_timer_t frame_time;
    while (game.running)
    {
        frame_time = get_time_msec();

        input(&game);
        update(&game);
        render(&game);
        platform_timer_t current_time = get_time_msec() - frame_time;
        if (current_time < FRAME_TIME)
        {
            time_delay(FRAME_TIME - current_time);
        }
    }

    // clean everything up
    game_cleanup(&game);
    return (EXIT_SUCCESS);
}

void input(Game_t *game)
{
    if (game->game_state == MENU)
        menu_input(game);
    else if (game->game_state == GAME)
        game_input(game);
}

void update(Game_t *game)
{
    if (game->game_state == MENU)
        menu_update(game);
    else if (game->game_state == GAME)
        game_update(game);
}

void render(Game_t *game)
{
    if (game->game_state == MENU)
        menu_render(game);
    else if (game->game_state == GAME)
        game_render(game);
}
