#ifndef MANAGER_H // This is called include guard
#define MANAGER_H // and it is a standard C idiom for header files

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "canvas.h"
#include "render.h"
#include "types.h"

struct Game
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Canvas canvas;
    CanvasRender canvas_render;
};

void sdl_cleanup(struct Game *game, int exit_status);
bool sdl_initialise(struct Game *game);

#endif