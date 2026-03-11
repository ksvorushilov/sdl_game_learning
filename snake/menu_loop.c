#include <stdbool.h>
#include <SDL2/SDL.h>

#include "collision.h"
#include "const.h"
#include "font.h"
#include "game_loop.h"
#include "snake.h"

void destroy_game(Game *game);

void menu_input(struct Game *game)
{
    // Phase 1: process the input
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            game->running = false;
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                game->running = false;
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                game->game_state = GAME;
        }
    }
    game->frame_time = SDL_GetTicks();
}

void menu_update(struct Game *game)
{
    if (game->snake != NULL)
        destroy_game(game);
    // do nothing
}
void menu_render(struct Game *game)
{
    // phase 2: render the scene
    //  set bg colour
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    // clear previous frame
    SDL_RenderClear(game->renderer);

    SDL_SetRenderDrawColor(game->renderer, 50, 100, 150, 255);

    print_sdl(game->renderer,
              "SNAKE",
              &(point_2d){250, 100},
              60);

    if (game->ever_lost)
        print_sdl(game->renderer,
                  "Game over. You did well.",
                  &(point_2d){150, 300},
                  20);
                  
    print_sdl(game->renderer,
              "press spacebar to start",
              &(point_2d){150, 500},
              20);

    // now display it on renderer
    SDL_RenderPresent(game->renderer);
}

void destroy_game(Game *game)
{
    game->ever_lost = true;
    destroy_snake(game->snake);
    game->snake = NULL;
}
