#include <stdio.h>
#include <stdlib.h> // for exit(), EXIT_FAILURE and EXIT_SUCCESS
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "canvas.h"
#include "const.h"
#include "font.h"
#include "manager.h"
#include "render.h"
#include "types.h" // point_2d
#include "slider.h"

bool is_canvas_hit(CanvasRender *canvas_render, SDL_Rect *brush);

int main(int argc, char *argv[])
{
    // INIT
    printf("Program starts.\n");
    struct Game game = {.window = NULL, .renderer = NULL}; // initialize struct with null pointers is recommended to avoid undefined behavior when accessing uninitialized pointers.
    if (!sdl_initialise(&game))
    {
        printf("NOT SUCCESS.\n");
        sdl_cleanup(&game, EXIT_FAILURE); // the program is terminated immediately here
    }
    printf("Initialised successfully.\n");

    bool running = true;
    Uint32 start_time = SDL_GetTicks();
    int step = 0;
    SDL_ShowCursor(SDL_DISABLE); // hide system mouse cursor

    Slider r_slider = {80, 20, 140, 100, 50, 1};
    Slider g_slider = {330, 20, 140, 100, 50, 1};
    Slider b_slider = {580, 20, 140, 100, 50, 1};

    Canvas canvas;
    printf("Initialising canvas...\n");
    if (!init_canvas(&canvas, &(point_2d){CANVAS_SIZE_W, CANVAS_SIZE_H}))
    {
        printf("Canvas not initialised.\n");
        destroy_canvas(&canvas);
        sdl_cleanup(&game, EXIT_FAILURE); // the program is terminated immediately here
    }
    printf("Canvas initialised.\n");

    CanvasRender canvas_render;
    if (!init_canvas_render(&canvas_render,
                            game.renderer,
                            &(point_2d){80, 120},
                            &(point_2d){CANVAS_SIZE_W, CANVAS_SIZE_H},
                            &(point_2d){CANVAS_RENDER_W, CANVAS_RENDER_H}))
    {
        printf("Canvas render not initialised.\n");
        destroy_canvas_render(&canvas_render);
        destroy_canvas(&canvas);
        sdl_cleanup(&game, EXIT_FAILURE); // the program is terminated immediately here
    }
    printf("Canvas render initialised.\n");

    while (running)
    {
        bool print_button_press = false;
        // Phase 1: process the input
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                printf("Gracefully quit.\n");
                destroy_canvas_render(&canvas_render);
                destroy_canvas(&canvas);
                sdl_cleanup(&game, EXIT_SUCCESS);
            }
            if (event.type == SDL_KEYDOWN)
            {
                // const Uint8 *keystate = SDL_GetKeyboardState(NULL); - chatgpt said it is too much and redundant
                // since we already have key in event
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    printf("Gracefully quit by pressing esc.\n");
                    destroy_canvas_render(&canvas_render);
                    destroy_canvas(&canvas);
                    sdl_cleanup(&game, EXIT_SUCCESS);
                }
            }
        }
        point_2d mouse;
        unsigned int mouse_state = SDL_GetMouseState(&mouse.x, &mouse.y);
        SDL_Rect cursor = {mouse.x, mouse.y, 50, 50};

        if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            print_button_press = true;
            if (is_slider_hit(&r_slider, &mouse))
                modify_slider_value(&r_slider, &mouse);
            if (is_slider_hit(&g_slider, &mouse))
                modify_slider_value(&g_slider, &mouse);
            if (is_slider_hit(&b_slider, &mouse))
                modify_slider_value(&b_slider, &mouse);

            if (is_canvas_hit(&canvas_render, &cursor))
            {
                draw(&canvas_render,
                     &canvas,
                     game.renderer,
                     &cursor,
                     pack_color(r_slider.value, g_slider.value, b_slider.value, 255));
            }
        }
        // phase 2: render the scene
        //  set bg colour
        SDL_SetRenderDrawColor(game.renderer, 80, 80, 80, 255);

        // clear previous frame
        SDL_RenderClear(game.renderer);

        SDL_Rect rect = {50, 240, 100, 100};
        point_2d pos = {50, 240};
        // here we can draw our own objects - which we will do
        SDL_SetRenderDrawColor(game.renderer, r_slider.value, 0, 0, 255);
        render_slider(game.renderer, &r_slider);
        SDL_SetRenderDrawColor(game.renderer, 0, g_slider.value, 0, 255);
        render_slider(game.renderer, &g_slider);
        SDL_SetRenderDrawColor(game.renderer, 0, 0, b_slider.value, 255);
        render_slider(game.renderer, &b_slider);
        // SDL_RenderDrawRect(game.renderer, &rect);

        // printf("drawing canvas...\n");
        render_canvas(&canvas_render, game.renderer, &canvas);

        SDL_SetRenderDrawColor(game.renderer, r_slider.value, g_slider.value, b_slider.value, 255);
        SDL_RenderFillRect(game.renderer, &cursor);

        // now display it on renderer
        SDL_RenderPresent(game.renderer);

        SDL_Delay(FRAME_TIME);
    }

    // clean everything up
    destroy_canvas_render(&canvas_render);
    destroy_canvas(&canvas);
    sdl_cleanup(&game, EXIT_SUCCESS);
}

bool is_canvas_hit(CanvasRender *canvas_render, SDL_Rect *brush)
{
    SDL_Rect dummy;
    return (SDL_TRUE == SDL_IntersectRect(&canvas_render->frame,
                                          brush,
                                          &dummy));
}
