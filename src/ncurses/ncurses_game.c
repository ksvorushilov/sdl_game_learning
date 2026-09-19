#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#include <ncurses.h>

#include "types.h"

#include "ncurses_bindings.h"

void process_game_input(Game_t *game)
{
    int32_t ch = wgetch(game->window.window);
    if (ch >= 'A' && ch <= 'Z') // uppercase guard
        ch = tolower(ch);
    if (ch == ERR)
    {
        return;
    }
    if (ch == 27) // escape value
    {
        game->running = false;
    }
    action_enum_t action = key_match(ch, BIND_GAME);

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
