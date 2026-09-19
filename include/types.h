#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#include "const.h"

typedef uint32_t platform_timer_t;

typedef struct game_window_t
{
    void *window;
} game_window_t;

typedef struct game_renderer_t
{
    void *renderer;
} game_renderer_t;

typedef struct
{
    int x;
    int y;
} point_2d;

typedef struct Snake
{
    point_2d pos;
    point_2d vel;
    struct Snake *next;
} Snake;

typedef enum
{
    MENU,
    GAME,
} GAME_STATE;

typedef struct Game_t
{

    game_window_t window;
    game_renderer_t renderer; 

    // control state
    bool running;
    bool ever_lost;

    // time
    platform_timer_t frame_time;
    platform_timer_t step_time;
    platform_timer_t game_timer;

    // snake
    Snake *snake;

    size_t snake_len;

    bool wraparound;

    // state enums
    SNAKE_VEL_STATE snake_vel_state;
    GAME_STATE game_state;

    unsigned int snake_speed;

    point_2d food[FOOD_QUANTITY];

} Game_t;

#endif
