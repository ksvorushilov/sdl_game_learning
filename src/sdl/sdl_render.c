#include <SDL2/SDL.h>

#include "ui_and_engine.h"
#include "manager.h"
#include "sdl_const.h"
#include "font.h"

typedef struct
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 alpha;

} render_color_t;

static const render_color_t BG_COLOR = {.r = 0,
                                        .g = 0,
                                        .b = 0,
                                        .alpha = 255};

static const render_color_t SNAKE_COLOR = {.r = 50,
                                           .g = 100,
                                           .b = 150,
                                           .alpha = 255};

static const render_color_t FOOD_COLOR = {.r = 150,
                                          .g = 100,
                                          .b = 50,
                                          .alpha = 255};

static void render_color_cell(Game_t *game, const int x, const int y);

void render_set_color(Game_t *game, render_color_t color)
{
    SDL_SetRenderDrawColor(game->renderer.renderer,
                           color.r,
                           color.g,
                           color.b,
                           color.alpha);
}

void render_clear_frame(Game_t *game)
{
    render_set_color(game, BG_COLOR);
    SDL_RenderClear(game->renderer.renderer);
}

void render_present(Game_t *game)
{
    SDL_RenderPresent(game->renderer.renderer);
}

void render_draw_snake(Game_t *game)
{
    render_set_color(game, SNAKE_COLOR);
    for (Snake *current_snake = game->snake; current_snake != NULL; current_snake = current_snake->next)
    {
        render_color_cell(game, current_snake->pos.x, current_snake->pos.y);
    }
}
void render_draw_food(Game_t *game)
{
    render_set_color(game, FOOD_COLOR);
    for (int i = 0; i < FOOD_QUANTITY; i++)
    {
        render_color_cell(game, game->food[i].x, game->food[i].y);
    }
}

void render_print_plain(Game_t *game, char *str_to_print, point_2d coord)
{
    print_sdl(game->renderer.renderer,
              str_to_print,
              &(point_2d){coord.x * SCREEN_CELL_WIDTH, coord.y * SCREEN_CELL_HEIGHT},
              10);
}
void render_print_title(Game_t *game, char *str_to_print, point_2d coord)
{
    print_sdl(game->renderer.renderer,
              str_to_print,
              &(point_2d){coord.x * SCREEN_CELL_WIDTH, coord.y * SCREEN_CELL_HEIGHT},
              20);
}

static void render_color_cell(Game_t *game, const int x, const int y)
{
    SDL_Rect rect = {x * SCREEN_CELL_WIDTH,
                     y * SCREEN_CELL_HEIGHT,
                     SCREEN_CELL_WIDTH,
                     SCREEN_CELL_HEIGHT};
    SDL_RenderFillRect(game->renderer.renderer, &rect);
}
