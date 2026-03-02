#include <stdio.h>
#include <stdlib.h> // for exit(), EXIT_FAILURE and EXIT_SUCCESS
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "const.h"
#include "font.h"
#include "manager.h"
#include "types.h" // point_2d
#include "slider.h"

int main(int argc, char *argv[])
{
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
    SDL_ShowCursor(SDL_DISABLE); // hide system cursor

    Slider r_slider = {80, 100, 140, 100, 50, 1};
    Slider g_slider = {330, 100, 140, 100, 50, 1};
    Slider b_slider = {580, 100, 140, 100, 50, 1};
    while (running)
    {
        bool print_button_press = false;
        // Phase 1: calculate the scene
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                printf("Gracefully quit.\n");
                sdl_cleanup(&game, EXIT_SUCCESS);
            }
            if (event.type == SDL_KEYDOWN)
            {
                // const Uint8 *keystate = SDL_GetKeyboardState(NULL); - chatgpt said it is too much and redundant
                // since we already have key in event
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    printf("Gracefully quit by pressing esc.\n");
                    sdl_cleanup(&game, EXIT_SUCCESS);
                }
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
        SDL_SetRenderDrawColor(game.renderer, 0x01, 0xBC, 0x0D, 255);
        point_2d mouse;
        unsigned int mouse_state = SDL_GetMouseState(&mouse.x, &mouse.y);

        if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            print_button_press = true;
            if (is_slider_hit(&r_slider, &mouse))
                modify_slider_value(&r_slider, &mouse);
            if (is_slider_hit(&g_slider, &mouse))
                modify_slider_value(&g_slider, &mouse);
            if (is_slider_hit(&b_slider, &mouse))
                modify_slider_value(&b_slider, &mouse);
        }
        SDL_SetRenderDrawColor(game.renderer, r_slider.value, 0, 0, 255);
        render_slider(game.renderer, &r_slider);
        SDL_SetRenderDrawColor(game.renderer, 0, g_slider.value, 0, 255);
        render_slider(game.renderer, &g_slider);
        SDL_SetRenderDrawColor(game.renderer, 0, 0, b_slider.value, 255);
        render_slider(game.renderer, &b_slider);
        SDL_Rect cursor = {mouse.x, mouse.y, 10, 10};

        if (print_button_press)
        {
            pos.x = 150;
            pos.y = 20;
            print_sdl(game.renderer, "Left Mouse Button Pressed", &pos, 20);
        }
        if (step > 0 || SDL_GetTicks() - start_time > 1000)
        {
            pos.x = 50;
            pos.y = 240;
            print_sdl(game.renderer, "testing", &pos, 50);

            if (step <= 0)
                step += 1;
        }

        if (step > 1 || SDL_GetTicks() - start_time > 2000)
        {
            pos.x = 450;
            print_sdl(game.renderer, "color", &pos, 50);
            if (step <= 1)
                step += 1;
        }

        if (step > 2 || SDL_GetTicks() - start_time > 3000)
        {
            pos.y = 350;
            pos.x = 200;
            print_sdl(game.renderer, "sliders", &pos, 50);
            if (step <= 2)
                step += 1;
        }
        rect.x = 220;
        rect.y = 500;
        rect.w = 20;
        rect.h = 20;
        if (step > 3 || SDL_GetTicks() - start_time > 4000)
        {
            pos.y = 500;
            pos.x = 220;

            print_sdl(game.renderer, "PRESS ESC TO EXIT", &pos, 20);

            if (step <= 3)
                step += 1;
        }

        // SDL_RenderDrawRect(game.renderer, &rect);

        SDL_SetRenderDrawColor(game.renderer, r_slider.value, g_slider.value, b_slider.value, 255);
        SDL_RenderFillRect(game.renderer, &cursor);

        // now display it on renderer
        SDL_RenderPresent(game.renderer);

        SDL_Delay(FRAME_TIME);
    }

    sdl_cleanup(&game, EXIT_SUCCESS);
}
