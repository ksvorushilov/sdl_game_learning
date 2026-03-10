#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "canvas.h"
#include "const.h"
#include "types.h"

bool bounds_check(Canvas *canvas, const point_2d *coord);

static SDL_PixelFormat *pixel_format = NULL;

bool init_canvas(Canvas *canvas, point_2d *size)
{
    if (size->x == 0 || size->y == 0)
        return false;

    if (!pixel_format)
    {
        pixel_format = SDL_AllocFormat(PROJECT_PIXEL_FORMAT);
        if (!pixel_format)
        {
            return false;
        }
    }
    canvas->data = malloc(size->x * size->y * sizeof(uint32_t));
    if (canvas->data == NULL)
        return false;
    canvas->size.x = size->x;
    canvas->size.y = size->y;
    fill_canvas(canvas);
    return true;
}

bool get_element(Canvas *canvas, point_2d *coord, uint32_t *var)
{
    if (!bounds_check(canvas, coord))
        return false;
    int num = canvas->size.x * coord->y + coord->x;
    *var = canvas->data[num];
    return true;
}

bool set_element(Canvas *canvas, point_2d *coord, uint32_t val)
{
    if (!bounds_check(canvas, coord))
        return false;
    int num = canvas->size.x * coord->y + coord->x;
    canvas->data[num] = val;
    return true;
}

void destroy_canvas(Canvas *canvas)
{
    SDL_FreeFormat(pixel_format);
    free(canvas->data);
}

bool bounds_check(Canvas *canvas, const point_2d *coord)
{
    if ((coord->x >= canvas->size.x) ||
        (coord->y >= canvas->size.y) ||
        (coord->x < 0) || (coord->y < 0))
        return false;
    return true;
}

void fill_canvas(Canvas *canvas)
{
    for (int x = 0; x < canvas->size.x; x++)
        for (int y = 0; y < canvas->size.y; y++)
            set_element(canvas,
                        &(point_2d){x, y},
                        pack_color(0, 50, 0, 255));
}

// this one needs refactoring, since we specified format in const
uint32_t pack_color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha)
{
    return SDL_MapRGBA(pixel_format, r, g, b, alpha);
}