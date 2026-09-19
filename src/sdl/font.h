#ifndef FONT_H // This is called include guard
#define FONT_H // and it is a standard C idiom for header files

// your header contents here

#include <SDL2/SDL.h>
#include "types.h"

#define PROJECT_PIXEL_FORMAT SDL_PIXELFORMAT_RGBA8888

#define FONT_WIDTH 7
#define FONT_HEIGHT 7
#define ALPHABET_LENGTH 36

void print_sdl(SDL_Renderer *renderer,
               const char *str,
               const point_2d *pos,
               unsigned int size);

void destroy_alphabet(void);

#endif // end of include guard