#include <math.h>
#include <stdbool.h>

#include "collision.h"
#include "const.h"
#include "game_loop.h"
#include "snake.h"
#include "ui_and_engine.h"
#include "food.h"

void init_game(Game_t *game);

void game_input(struct Game_t *game)
{
    // Phase 1: process the input
    process_game_input(game);
    game->frame_time = get_time_msec();
}

void game_update(struct Game_t *game)
{
    if (game->snake == NULL)
    {
        init_game(game);
        return;
    }

    if (get_time_msec() - game->step_time >
        INIT_SNAKE_STEP_TIME * pow(950, game->snake_speed) /
            pow(1000, game->snake_speed))
    {
        change_vel(game->snake, game->snake_vel_state);

        point_2d collision_test_point = {
            .x = game->snake->pos.x + game->snake->vel.x,
            .y = game->snake->pos.y + game->snake->vel.y};

        COLLISION col = collision_test(game, &collision_test_point);

        if (col == COLLISION_BORDER)
        {
            if (!game->wraparound)
            {
                game->game_state = MENU;
                return;
            }
        }
        if (col == COLLISION_SELF)
        {
            game->game_state = MENU;
            return;
        }
        else if (col == COLLISION_FOOD)
        {
            snake_move_and_grow(game->snake);
            game->snake_len += 1;
            if ((game->snake_len + FOOD_QUANTITY) == FIELD_HEIGHT * FIELD_WIDTH)
            {
                game->game_state = MENU;
            }
            food_reroll_by_value(&collision_test_point, game);
            game->snake_speed += 1;
        }
        else
            snake_move(game->snake);

        game->step_time = get_time_msec();
    }
}
void game_render(struct Game_t *game)
{
    // phase 2: render the scene
    //  set bg colour
    // render_set_bg_color(game);
    // clear previous frame
    render_clear_frame(game);

    // render_set_snake_color(game);
    render_draw_snake(game);

    // render_set_food_color(game);
    render_draw_food(game);

    // now display it on renderer
    render_present(game);
}

void init_game(Game_t *game)
{
    game->snake_vel_state = OFF;

    game->snake_len = 1;

    game->snake_speed = 1;

    create_snake_node(&game->snake, 10, 10, 1, 0);

    food_generate(game);

    game->step_time = get_time_msec();
}
