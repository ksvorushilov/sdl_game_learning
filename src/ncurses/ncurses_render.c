#include <ncurses.h>

#include "types.h"
#include "ncurses_render.h"


void render_color_cell(Game_t *game, const int x, const int y, RENDER_COLOR_t color);

void init_colors(void)
{
    init_pair(RENDER_COLOR_BG, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(RENDER_COLOR_TEXT, COLOR_WHITE, COLOR_BLUE);
    init_pair(RENDER_COLOR_SNAKE, COLOR_GREEN, COLOR_GREEN);
    init_pair(RENDER_COLOR_FOOD, COLOR_RED, COLOR_RED);
}

void render_clear_frame(Game_t *game)
{
    werase(game->window.window);
    // during clear, SDL fills frame with color (if I remember correctly).
    // We will do the same in ncurses
    wbkgd(game->window.window, COLOR_PAIR(RENDER_COLOR_BG));
}

void render_present(Game_t *game)
{
    wrefresh(game->window.window);
}

void render_draw_snake(Game_t *game)
{
    // render snake
    for (Snake *current_snake = game->snake; current_snake != NULL; current_snake = current_snake->next)
    {
        render_color_cell(game, current_snake->pos.x, current_snake->pos.y, RENDER_COLOR_SNAKE);
    }
}
void render_draw_food(Game_t *game)
{
    for (int i = 0; i < FOOD_QUANTITY; i++)
    {
        render_color_cell(game, game->food[i].x, game->food[i].y, RENDER_COLOR_FOOD);
    }
}

void render_print_plain(Game_t *game, char *str_to_print, point_2d coord)
{
    mvwprintw(game->window.window, coord.y, coord.x * SYMBOLS_PER_CELL, str_to_print);
}
void render_print_title(Game_t *game, char *str_to_print, point_2d coord)
{
    mvwprintw(game->window.window, coord.y, coord.x * SYMBOLS_PER_CELL, str_to_print);
}

void render_color_cell(Game_t *game, const int x, const int y, RENDER_COLOR_t color)
{
    // int mvwchgat(WINDOW * win, int y, int x, int n, attr_t attr, short color, const void *opts);
    for (int i = 0; i < SYMBOLS_PER_CELL; i++)
    {
        mvwchgat(game->window.window,
                 y,
                 SYMBOLS_PER_CELL * x + i,
                 1,
                 A_NORMAL,
                 color,
                 NULL);
    }
}
