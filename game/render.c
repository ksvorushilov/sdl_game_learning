#include <stdbool.h>
#include <SDL2/SDL.h>

#include "const.h"
#include "font.h"
#include "manager.h"
#include "render.h"
#include "types.h" // point_2d
#include "slider.h"
#include "canvas.h"

void render_grid(CanvasRender *canvas_render, Canvas *canvas, SDL_Renderer *renderer);

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
    render_grid(canvas_render, canvas, renderer);
    return true;
}

bool draw(CanvasRender *canvas_render,
          Canvas *canvas,
          SDL_Renderer *renderer,
          SDL_Rect *brush,
          uint32_t val)
{

    if (!SDL_HasIntersection(&canvas_render->frame, brush))
        return false;
    int w = canvas->size.x;
    int h = canvas->size.y;

    if (h == 0 || w == 0)
        return false;

    int render_w = canvas_render->frame.w;
    int render_h = canvas_render->frame.h;

    int mod_x = (brush->x - canvas_render->frame.x) * w / render_w;
    int mod_y = (brush->y - canvas_render->frame.y) * h / render_h;

    int mod_w = brush->w * w / render_w;
    int mod_h = brush->h * h / render_h;

    return simple_brush(canvas, &(SDL_Rect){mod_x, mod_y, mod_w, mod_h}, val);
}

void render_grid(CanvasRender *canvas_render, Canvas *canvas, SDL_Renderer *renderer)
{
    // backup
    SDL_BlendMode old_mode;
    SDL_GetRenderDrawBlendMode(renderer, &old_mode);

    uint8_t r, g, b, alpha;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &alpha);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 30, 60, 90, 255);

    int x_start = canvas_render->frame.x;
    int x_end = canvas_render->frame.x + canvas_render->frame.w;
    int y_start = canvas_render->frame.y;
    int y_end = canvas_render->frame.y + canvas_render->frame.h;

    for (int x = 0; x < canvas->size.x + 1; x++)
    {
        SDL_RenderDrawLine(renderer,
                           x_start + x * CANVAS_SCALE,
                           y_start,
                           x_start + x * CANVAS_SCALE,
                           y_end);
    }
    for (int y = 0; y < canvas->size.y + 1; y++)
    {
        SDL_RenderDrawLine(renderer,
                           x_start,
                           y_start + y * CANVAS_SCALE,
                           x_end,
                           y_start + y * CANVAS_SCALE);
    }
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_SetRenderDrawBlendMode(renderer, old_mode);
}

bool is_canvas_hit(CanvasRender *canvas_render, SDL_Rect *brush)
{
    return (SDL_TRUE == SDL_HasIntersection(&canvas_render->frame,
                                            brush));
}

bool simple_brush(Canvas *canvas, SDL_Rect *modified_area, uint32_t val)
{
    for (int x = modified_area->x; x < modified_area->x + modified_area->w; x++)
        for (int y = modified_area->y; y < modified_area->y + modified_area->h; y++)
            if (!set_element(canvas, &(point_2d){x, y}, val))
                ;
    return true;
}