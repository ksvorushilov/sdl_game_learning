#include <stdbool.h>
#include <SDL2/SDL.h>

#include "const.h"
#include "font.h"
#include "manager.h"
#include "render.h"
#include "types.h" // point_2d
#include "slider.h"
#include "canvas.h"

bool init_canvas_render(CanvasRender *canvas_render,
                        SDL_Renderer *renderer,
                        point_2d *pos,
                        point_2d *texture_size,
                        point_2d *render_size)
{
    canvas_render->texture = SDL_CreateTexture(
        renderer,
        PROJECT_PIXEL_FORMAT,
        SDL_TEXTUREACCESS_STREAMING,
        texture_size->x,
        texture_size->y);

    canvas_render->frame.x = pos->x;
    canvas_render->frame.y = pos->y;
    canvas_render->frame.w = render_size->x;
    canvas_render->frame.h = render_size->y;

    return (canvas_render->texture != NULL);
}

void destroy_canvas_render(CanvasRender *canvas_render)
{
    SDL_DestroyTexture(canvas_render->texture);
}

bool render_canvas(CanvasRender *canvas_render,
                   SDL_Renderer *renderer,
                   Canvas *canvas)
{
    size_t row_size = canvas->size.x * sizeof(uint32_t);
    SDL_Rect rect = {0, 0, canvas->size.x, canvas->size.y};
    int is_success = SDL_UpdateTexture(canvas_render->texture,
                                       &rect,
                                       canvas->data, row_size);
    if (is_success < 0)
        return false;

    SDL_RenderCopy(renderer, canvas_render->texture, NULL, &canvas_render->frame);
    return true;
}

bool draw(CanvasRender *canvas_render,
          Canvas *canvas,
          SDL_Renderer *renderer,
          SDL_Rect *brush,
          uint32_t val)
{
    SDL_Rect res;
    if (!SDL_IntersectRect(&canvas_render->frame, brush, &res))
        return false;
    size_t w = canvas->size.x;
    size_t h = canvas->size.y;

    size_t render_w = canvas_render->frame.w;
    size_t render_h = canvas_render->frame.h;

    size_t mod_x = (brush->x - canvas_render->frame.x) * w / render_w;
    size_t mod_y = (brush->y - canvas_render->frame.y) * h / render_h;

    size_t mod_w = brush->w * w / render_w;
    size_t mod_h = brush->h * h / render_h;

    return simple_brush(canvas, &(SDL_Rect){mod_x, mod_y, mod_w, mod_h}, val);
    // TODO: calculate points to be modified, create brush logic, change ambiguous name of function

    // return true;
}

bool simple_brush(Canvas *canvas, SDL_Rect *modified_area, uint32_t val)
{
    for (int x = modified_area->x; x < modified_area->x + modified_area->w; x++)
        for (int y = modified_area->y; y < modified_area->y + modified_area->h; y++)
            if (!set_element(canvas, &(point_2d){x, y}, val))
                return false;
    return true;
}