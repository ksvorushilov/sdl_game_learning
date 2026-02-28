#ifndef SLIDER_H  // This is called include guard
#define SLLIDER_H // and it is a standard C idiom for header files

// your header contents here

#include <SDL2/SDL.h>
#include "types.h"

typedef struct
{
    int x;
    int y;
    int w;
    int h;
    int value;
    int step;
} Slider;

void render_slider(SDL_Renderer *renderer, Slider *slider);
bool is_slider_hit(Slider *slider, point_2d *mouse);
bool modify_slider_value(Slider *slider, point_2d *mouse);

#endif