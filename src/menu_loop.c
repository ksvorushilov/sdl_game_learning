#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "collision.h"
#include "const.h"
#include "game_loop.h"
#include "snake.h"
#include "ui_and_engine.h"

void destroy_game(Game_t *game);

void menu_input(struct Game_t *game)
{
    // Phase 1: process the input
    process_menu_input(game);
}

void menu_update(struct Game_t *game)
{
    if (game->snake != NULL)
        destroy_game(game);
    // do nothing
}
void menu_render(struct Game_t *game)
{
    // phase 2: render the scene
    //  set bg colour

    // render_set_bg_color(game);
    // clear previous frame
    render_clear_frame(game);

    // render_set_text_color(game);

    render_print_title(game, "SNAKE", (point_2d){18, 5});

    if (game->ever_lost)
    {
        render_print_plain(game, "Game over. You did well.", (point_2d){15, 15});
    }
    render_print_plain(game, "press spacebar to start", (point_2d){15, 25});
    render_print_plain(game, "wrap snake around field (t to toggle):", (point_2d){10, 27});
    render_print_plain(game,
                       game->wraparound ? "YES" : "NO",
                       (point_2d){33, 27});

    // now display it on renderer
    render_present(game);
}

void destroy_game(Game_t *game)
{
    game->ever_lost = true;
    destroy_snake(game->snake);
    game->snake = NULL;
}
