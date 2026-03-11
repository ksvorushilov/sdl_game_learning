#include <stdbool.h>
#include <SDL2/SDL.h>

#include "collision.h"
#include "const.h"
#include "game_loop.h"
#include "snake.h"

void init_game(Game *game);

void game_input(struct Game *game)
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
            if (event.key.keysym.scancode == SDL_SCANCODE_UP)
                game->snake_vel_state = UP;
            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
                game->snake_vel_state = LEFT;
            if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
                game->snake_vel_state = DOWN;
            if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                game->snake_vel_state = RIGHT;
        }
    }
    game->frame_time = SDL_GetTicks();
}

void game_update(struct Game *game)
{
    if (game->snake == NULL)
    {
        init_game(game);
        return;
    }

    if (SDL_GetTicks() - game->step_time > INIT_SNAKE_SPEED / game->snake_speed_divider)
    {
        change_vel(game->snake, game->snake_vel_state);

        point_2d collision_test_point = {
            .x = game->snake->pos.x + game->snake->vel.x,
            .y = game->snake->pos.y + game->snake->vel.y};

        COLLISION col = collision_test(game, &collision_test_point);

        if (col == COLLISION_BORDER || col == COLLISION_SELF)
        {
            game->game_state = MENU;
            return;
        }
        else if (col == COLLISION_FOOD)
        {
            move_and_grow(game->snake);
            generate_food(game->food, game->snake);
            game->snake_speed_divider += 1;
        }
        else
            move(game->snake);

        game->step_time = SDL_GetTicks();
    }
}
void game_render(struct Game *game)
{
    // phase 2: render the scene
    //  set bg colour
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    // clear previous frame
    SDL_RenderClear(game->renderer);

    SDL_SetRenderDrawColor(game->renderer, 50, 100, 150, 255);
    SDL_Rect rect = {0, 0, FIELD_SCALE, FIELD_SCALE};

    // render snake
    for (Snake *current_snake = game->snake; current_snake != NULL; current_snake = current_snake->next)
    {
        rect.x = current_snake->pos.x * FIELD_SCALE;
        rect.y = current_snake->pos.y * FIELD_SCALE;
        SDL_RenderFillRect(game->renderer, &rect);
    }

    
    SDL_SetRenderDrawColor(game->renderer, 150, 100, 50, 255);
    for (int i = 0; i < FOOD_QUANTITY; i++)
    {
        rect.x = game->food[i].x * FIELD_SCALE;
        rect.y = game->food[i].y * FIELD_SCALE;
        SDL_RenderFillRect(game->renderer, &rect);
    }
    // now display it on renderer
    SDL_RenderPresent(game->renderer);
}

void init_game(Game *game)
{
    game->snake_vel_state = OFF;

    game->snake_speed_divider = 1;

    create_snake_node(&game->snake, 10, 10, 1, 0);

    generate_food(game->food, game->snake);

    game->step_time = SDL_GetTicks();
}
