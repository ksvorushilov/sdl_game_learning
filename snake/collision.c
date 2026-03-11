
#include <stdbool.h>
#include <stdlib.h> // rand

#include "collision.h"
#include "const.h"
#include "manager.h"
#include "types.h"

bool collision_test_food(point_2d food[FOOD_QUANTITY], point_2d *point);
bool collision_test_self(Snake *snake, point_2d *point);
bool collision_test_border(point_2d *point);

COLLISION collision_test(Game *game, point_2d *point)
{
    if (collision_test_border(point))
        return COLLISION_BORDER;
    else if (collision_test_food(game->food, point))
        return COLLISION_FOOD;
    else if (collision_test_self(game->snake->next, point)) //by design of collision test self
        return COLLISION_SELF;
    else
        return COLLISION_NONE;
}

bool collision_test_food(point_2d food[FOOD_QUANTITY], point_2d *point)
{
    for (int i = 0; i < FOOD_QUANTITY; i++)
    {
        if ((point->x == food[i].x) && (point->y == food[i].y))
            return true;
    }
    return false;
}

bool collision_test_self(Snake *snake, point_2d *point)
{
    if (snake == NULL)
        return false;
        
    for (Snake *current_snake = snake;
         current_snake != NULL;
         current_snake = current_snake->next)
    {
        if ((point->x == current_snake->pos.x) && (point->y == current_snake->pos.y))
            return true;
    }
    return false;
}

bool collision_test_border(point_2d *point)
{
    return (point->x < 0 || point->x >= FIELD_WIDTH ||
            point->y < 0 || point->y >= FIELD_HEIGHT);
}