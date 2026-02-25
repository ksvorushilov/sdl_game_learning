#ifndef FONT_H // This is called include guard
#define FONT_H // and it is a standard C idiom for header files

// your header contents here

#include <SDL2/SDL.h>

#define FONT_WIDTH 7
#define FONT_HEIGHT 7
#define ALPHABET_LENGTH 26

void generate_alphabet(SDL_Renderer *renderer,
                       SDL_Texture *alphabet[ALPHABET_LENGTH]);

#endif // end of include guard