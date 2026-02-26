#ifndef FONT_H // This is called include guard
#define FONT_H // and it is a standard C idiom for header files

// your header contents here

#include <SDL2/SDL.h>
#include "types.h"

#define FONT_WIDTH 7
#define FONT_HEIGHT 7
#define ALPHABET_LENGTH 36

void generate_alphabet(SDL_Renderer *renderer,
                       SDL_Texture *alphabet[ALPHABET_LENGTH]);

void print_sdl(SDL_Renderer *renderer,
               SDL_Texture *alphabet[ALPHABET_LENGTH],
               string str,
               point_2d *pos,
               unsigned int size);

#endif // end of include guard