#ifndef RENDER_H // This is called include guard
#define RENDER_H // and it is a standard C idiom for header files

#include <SDL2/SDL.h>

#include "canvas.h"
typedef struct
{
    SDL_Texture *texture;
    SDL_Rect frame;
} CanvasRender;

typedef bool (*BRUSH_FN)(Canvas *canvas, SDL_Rect *modified_area);

bool init_canvas_render(CanvasRender *canvas_render,
                        SDL_Renderer *renderer,
                        point_2d *pos,
                        point_2d *canvas_size,
                        point_2d *render_size);

void destroy_canvas_render(CanvasRender *canvas_render);

bool draw(CanvasRender *canvas_render,
          Canvas *canvas,
          SDL_Renderer *renderer,
          SDL_Rect *brush,
          uint32_t val);

bool render_canvas(CanvasRender *canvas_render,
                   SDL_Renderer *renderer,
                   Canvas *canvas);

bool simple_brush(Canvas *canvas, SDL_Rect *modified_area, uint32_t val);

#endif