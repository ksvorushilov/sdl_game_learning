#ifndef MANAGER_H
#define MANAGER_H 

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "const.h"
#include "types.h"

typedef enum {
    MENU,
    GAME,
} GAME_STATE;

typedef struct Game
{
    // SDL necessary tools
    SDL_Window *window;
    SDL_Renderer *renderer;

    // control state
    bool running;
    bool ever_lost;

    // time
    Uint32 frame_time;
    Uint32 step_time;

    // snake
    Snake *snake;

    // state enums
    SNAKE_VEL_STATE snake_vel_state;
    GAME_STATE game_state;

    unsigned int snake_speed_divider;

    point_2d food[FOOD_QUANTITY];

} Game;

void sdl_cleanup(struct Game *game);
bool sdl_initialise(struct Game *game);

#endif