#include <stdbool.h>

#include <ncurses.h>

#include "ui_and_engine.h"
#include "manager.h"

#include "ncurses_engine.h"

void process_menu_input(Game_t *game)
{
    int ch = wgetch(game->window.window);
    if (ch == ERR)
    {
        return;
    }
    if (ch == 27) // escape value
    {
        game->running = false;
    }
    else if (ch == ' ')
    {
        game->game_state = GAME;
    }
    else if (ch == 't')
    {
        game->wraparound ^= 1;
    }
}
