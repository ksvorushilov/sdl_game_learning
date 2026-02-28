#include <stdbool.h>
#include <SDL2/SDL.h>
#include "font.h"
#include "slider.h"

#define MIN_SLIDER_VALUE 0
#define MAX_SLIDER_VALUE 255

void render_slider(SDL_Renderer *renderer, Slider *slider)
{
    int center_left_x = slider->x;
    int center_right_x = slider->x + slider->w;
    int center_y = slider->y + slider->h / 2;
    int upper_center_x = center_left_x + (center_right_x - center_left_x) / 2;
    int upper_center_y = center_y - slider->h / 4;

    int cursor_pos = center_left_x + slider->w * (slider->value - MIN_SLIDER_VALUE) / (MAX_SLIDER_VALUE - MIN_SLIDER_VALUE);
    int cursor_w = slider->w / 16 + 1; // magic number - to fix
    int cursor_h = slider->h / 4 + 1;  // magic number - to fix

    SDL_Rect slider_cursor = {cursor_pos - cursor_w / 2, center_y - cursor_h / 2, cursor_w, cursor_h};

    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // magic number - to fix
    SDL_RenderDrawLine(renderer, center_left_x, center_y, center_right_x, center_y);
    SDL_RenderFillRect(renderer, &slider_cursor);

    char value_str[10]; // magic number - to fix
    sprintf(value_str, "%d", slider->value);
    point_2d text_pos = {upper_center_x, upper_center_y};

    print_sdl(renderer, value_str, &text_pos, 10);
}

bool is_slider_hit(Slider *slider, point_2d *mouse)
{
    return mouse->x >= slider->x &&
           mouse->x < slider->x + slider->w &&
           mouse->y >= slider->y &&
           mouse->y < slider->y + slider->h;
}

bool modify_slider_value(Slider *slider, point_2d *mouse)
{
    int new_value = (MAX_SLIDER_VALUE - MIN_SLIDER_VALUE) * (mouse->x - slider->x) / slider->w;
    if (new_value > 255)
        new_value = 255;
    if (new_value < 0)
        new_value = 0;
    slider->value = new_value;
    return true;
}