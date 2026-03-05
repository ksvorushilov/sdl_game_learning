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

#define INIT_CURSOR_SIZE 20

int main(int argc, char *argv[])
{
    // INIT
    printf("Program starts.\n");
    struct Game game = {0}; // initialize struct with null pointers is recommended to avoid undefined behavior when accessing uninitialized pointers.
    if (!sdl_initialise(&game))
    {
        printf("NOT SUCCESS.\n");
        sdl_cleanup(&game, EXIT_FAILURE); // the program is terminated immediately here
        return (EXIT_FAILURE);
    }
    printf("Initialised successfully.\n");

    bool running = true;

    SDL_ShowCursor(SDL_DISABLE); // hide system mouse cursor

    Slider r_slider = {
        .x = 40,
        .y = 0,
        .w = 140,
        .h = 50,
        .value = 50,
        .step = 1};
    Slider g_slider = {
        .x = 40 + 200,
        .y = 0,
        .w = 140,
        .h = 50,
        .value = 50,
        .step = 1};
    Slider b_slider = {
        .x = 40 + 400,
        .y = 0,
        .w = 140,
        .h = 50,
        .value = 50,
        .step = 1};
    Slider s_slider = {
        .x = 40 + 600,
        .y = 0,
        .w = 140,
        .h = 50,
        .value = 50,
        .step = 1};

    SDL_Rect cursor = {0, 0, INIT_CURSOR_SIZE, INIT_CURSOR_SIZE};
    while (running)
    {
        Uint32 start_time = SDL_GetTicks();
        // Phase 1: process the input
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                printf("Gracefully quit.\n");
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    printf("Gracefully quit by pressing esc.\n");
                    running = false;
                }
            }
        }
        point_2d mouse;
        unsigned int mouse_state = SDL_GetMouseState(&mouse.x, &mouse.y);
        cursor.x = mouse.x;
        cursor.y = mouse.y;

        if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if (is_slider_hit(&r_slider, &mouse))
                modify_slider_value(&r_slider, &mouse);
            if (is_slider_hit(&g_slider, &mouse))
                modify_slider_value(&g_slider, &mouse);
            if (is_slider_hit(&b_slider, &mouse))
                modify_slider_value(&b_slider, &mouse);
            if (is_slider_hit(&s_slider, &mouse))
                modify_slider_value(&s_slider, &mouse);

            if (is_canvas_hit(&game.canvas_render, &cursor))
            {
                draw(&game.canvas_render,
                     &game.canvas,
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

        // here we can draw our own objects - which we will do
        SDL_SetRenderDrawColor(game.renderer, r_slider.value, 0, 0, 255);
        render_slider(game.renderer, &r_slider);
        SDL_SetRenderDrawColor(game.renderer, 0, g_slider.value, 0, 255);
        render_slider(game.renderer, &g_slider);
        SDL_SetRenderDrawColor(game.renderer, 0, 0, b_slider.value, 255);
        render_slider(game.renderer, &b_slider);
        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
        render_slider(game.renderer, &s_slider);

        render_canvas(&game.canvas_render, game.renderer, &game.canvas);

        SDL_SetRenderDrawColor(game.renderer, r_slider.value, g_slider.value, b_slider.value, 255);
        cursor.h = s_slider.value;
        cursor.w = s_slider.value;
        SDL_RenderFillRect(game.renderer, &cursor);

        // now display it on renderer
        SDL_RenderPresent(game.renderer);

        Uint32 current_frame_time = SDL_GetTicks() - start_time;
        if (current_frame_time < FRAME_TIME)
            SDL_Delay(FRAME_TIME - current_frame_time);
    }

    // clean everything up
    SDL_ShowCursor(SDL_ENABLE);
    sdl_cleanup(&game, EXIT_SUCCESS);
    return (EXIT_SUCCESS);
}
