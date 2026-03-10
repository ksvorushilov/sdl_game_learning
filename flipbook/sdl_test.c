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

enum
{
    CURSOR_OFF,
    CURSOR_R_SLIDER,
    CURSOR_G_SLIDER,
    CURSOR_B_SLIDER,
    CURSOR_SIZE_SLIDER,
    CURSOR_CANVAS_DRAW,
};

void input(struct Game *game);
void update(struct Game *game);
void render(struct Game *game);
void handle_slider(Slider *slider, Mouse *mouse, int *current_state, const int intended_state);

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

    game.running = true;

    game.r_slider = (Slider){
        .x = 40,
        .y = 0,
        .w = 140,
        .h = 50,
        .value = 50,
        .step = 1};
    game.g_slider = (Slider){
        .x = 40 + 200,
        .y = 0,
        .w = 140,
        .h = 50,
        .value = 50,
        .step = 1};
    game.b_slider = (Slider){
        .x = 40 + 400,
        .y = 0,
        .w = 140,
        .h = 50,
        .value = 50,
        .step = 1};
    game.s_slider = (Slider){
        .x = 40 + 600,
        .y = 0,
        .w = 140,
        .h = 50,
        .value = 50,
        .step = 1};

    game.cursor = (SDL_Rect){0,
                             0,
                             INIT_CURSOR_SIZE,
                             INIT_CURSOR_SIZE};

    while (game.running)
    {
        Uint32 start_time = SDL_GetTicks();
        input(&game);
        update(&game);
        render(&game);

        Uint32 current_frame_time = SDL_GetTicks() - start_time;
        if (current_frame_time < FRAME_TIME)
            SDL_Delay(FRAME_TIME - current_frame_time);
    }

    // clean everything up
    sdl_cleanup(&game, EXIT_SUCCESS);
    return (EXIT_SUCCESS);
}

void input(struct Game *game)
{
    // Phase 1: process the input
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            printf("Gracefully quit.\n");
            game->running = false;
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                printf("Gracefully quit by pressing esc.\n");
                game->running = false;
            }
        }
    }
    game->mouse.state = SDL_GetMouseState(&game->mouse.position.x, &game->mouse.position.y);
}

void update(struct Game *game)
{

    game->cursor.x = game->mouse.position.x - game->cursor.w / 2;
    game->cursor.y = game->mouse.position.y - game->cursor.h / 2;

    if (game->mouse.state & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        handle_slider(&game->r_slider, &game->mouse, &game->cursor_state, CURSOR_R_SLIDER);
        handle_slider(&game->g_slider, &game->mouse, &game->cursor_state, CURSOR_G_SLIDER);
        handle_slider(&game->b_slider, &game->mouse, &game->cursor_state, CURSOR_B_SLIDER);
        handle_slider(&game->s_slider, &game->mouse, &game->cursor_state, CURSOR_SIZE_SLIDER);

        if ((game->cursor_state == CURSOR_CANVAS_DRAW) ||
            (game->cursor_state == CURSOR_OFF &&
             is_canvas_hit(&game->canvas_render, &game->cursor)))
        {
            if (game->cursor_state == CURSOR_OFF)
                game->cursor_state = CURSOR_CANVAS_DRAW;
            draw(&game->canvas_render,
                 &game->canvas,
                 game->renderer,
                 &game->cursor,
                 pack_color(game->r_slider.value, game->g_slider.value, game->b_slider.value, 255));
        }
    }
    else
    {
        game->cursor_state = CURSOR_OFF;
    }
}
void render(struct Game *game)
{
    // phase 2: render the scene
    //  set bg colour
    SDL_SetRenderDrawColor(game->renderer, 80, 80, 80, 255);
    // clear previous frame
    SDL_RenderClear(game->renderer);

    // here we can draw our own objects - which we will do
    SDL_SetRenderDrawColor(game->renderer, game->r_slider.value, 0, 0, 255);
    render_slider(game->renderer, &game->r_slider);
    SDL_SetRenderDrawColor(game->renderer, 0, game->g_slider.value, 0, 255);
    render_slider(game->renderer, &game->g_slider);
    SDL_SetRenderDrawColor(game->renderer, 0, 0, game->b_slider.value, 255);
    render_slider(game->renderer, &game->b_slider);
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    render_slider(game->renderer, &game->s_slider);

    render_canvas(&game->canvas_render, game->renderer, &game->canvas);

    SDL_SetRenderDrawColor(game->renderer, game->r_slider.value, game->g_slider.value, game->b_slider.value, 255);
    game->cursor.h = game->s_slider.value;
    game->cursor.w = game->s_slider.value;
    SDL_RenderFillRect(game->renderer, &game->cursor);

    // now display it on renderer
    SDL_RenderPresent(game->renderer);
}

void handle_slider(Slider *slider, Mouse *mouse, int *current_state, const int intended_state)
{
    if ((*current_state == intended_state) ||
        (*current_state == CURSOR_OFF &&
         is_slider_hit(slider, &mouse->position)))
    {
        if (*current_state == CURSOR_OFF)
            *current_state = intended_state;
        modify_slider_value(slider, &mouse->position);
    }
}
