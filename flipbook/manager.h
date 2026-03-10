#ifndef MANAGER_H // This is called include guard
#define MANAGER_H // and it is a standard C idiom for header files

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "canvas.h"
#include "render.h"
#include "slider.h"
#include "types.h"

typedef struct Mouse
{
    point_2d position;
    unsigned int state;
} Mouse;

struct Game
{
    // SDL necessary tools
    SDL_Window *window;
    SDL_Renderer *renderer;

    // control state
    bool running;

    // time
    Uint32 frame_time;

    // Canvas and CanvasRender objects
    Canvas canvas;
    CanvasRender canvas_render;

    // sliders (first version, better UI layout to consider)
    Slider r_slider, g_slider, b_slider, s_slider;

    // mouse control and button press state.
    Mouse mouse;

    // Mouse cursor, that in this context means brush
    SDL_Rect cursor;
    int cursor_state;
};

void sdl_cleanup(struct Game *game, int exit_status);
bool sdl_initialise(struct Game *game);

#endif