#ifndef CANVAS_H // This is called include guard
#define CANVAS_H // and it is a standard C idiom for header files

#include <stdint.h>
#include <stdbool.h>
#include "types.h"

typedef struct
{
    uint32_t *data;
    point_2d size;
} Canvas;

bool init_canvas(Canvas *canvas, point_2d *size);
bool get_element(Canvas *canvas, point_2d *coord, uint32_t *var);
bool set_element(Canvas *canvas, point_2d *coord, uint32_t val);
void fill_canvas(Canvas *canvas);
void destroy_canvas(Canvas *canvas);
uint32_t pack_color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);

#endif