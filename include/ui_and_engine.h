#ifndef UI_AND_ENGINE_H
#define UI_AND_ENGINE_H

#include <stdint.h>

#include "types.h"

// init
int engine_init();
game_window_t engine_create_window(int w, int h);
game_renderer_t engine_create_renderer(game_window_t window);
void engine_destroy_renderer(game_renderer_t renderer);
void engine_destroy_window(game_window_t window);
void engine_quit();

// time
platform_timer_t get_time_msec();
void time_delay(uint32_t val);

// input
void process_menu_input(Game_t *game);
void process_game_input(Game_t *game);

// render
void render_set_bg_color(Game_t *game);
void render_set_food_color(Game_t *game);
void render_set_snake_color(Game_t *game);
void render_set_text_color(Game_t *game);
void render_draw_snake(Game_t *game);
void render_draw_food(Game_t *game);
void render_print_plain(Game_t *game, char *str_to_print, point_2d coord);
void render_print_title(Game_t *game, char *str_to_print, point_2d coord);
void render_present(Game_t *game);
void render_clear_frame(Game_t *game);

#endif
