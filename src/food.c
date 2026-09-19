#include <stdlib.h>
#include <stdio.h>

#include "collision.h"
#include "food.h"
#include "manager.h"
#include "snake.h"
#include "types.h"

void food_generate(Game_t *game)
{
    for (int i = 0; i < FOOD_QUANTITY; i++)
    {
        food_reroll_instance(i, game);
    }
}

void food_reroll_by_value(const point_2d *value, Game_t *game)
{
    for (int i = 0; i < FOOD_QUANTITY; i++)
    {
        if ((value->x == game->food[i].x) && (value->y == game->food[i].y))
        {
            food_reroll_instance(i, game);
        }
    }
}

void food_reroll_instance(size_t i, Game_t *game)
{
    // WARNING: late-game unsafe
    while (1)
    {
        int x = rand() % FIELD_WIDTH;
        int y = rand() % FIELD_HEIGHT;
        point_2d new_pos = {x, y};

        COLLISION test_result = collision_test(game, &new_pos);

        if (test_result == COLLISION_NONE)
        {
            game->food[i] = new_pos;
            return;
        }
    }
}
