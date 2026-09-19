#include <stdbool.h>
#include <stdio.h> //debug only
#include <stdlib.h>

#include "const.h"
#include "snake.h"
#include "types.h"

bool create_snake_node(Snake **snake, int x, int y, int vel_x, int vel_y)
{
    if (vel_x < -1 || vel_x > 1 ||
        vel_y < -1 || vel_y > 1 ||
        vel_x + vel_y < -1 || vel_x + vel_y > 1)
        return false;

    *snake = malloc(sizeof(Snake));
    if (*snake == NULL)
        return false;

    (*snake)->pos.x = x;
    (*snake)->pos.y = y;
    (*snake)->vel.x = vel_x;
    (*snake)->vel.y = vel_y;

    (*snake)->next = NULL;
    return true;
}

void destroy_snake(Snake *snake)
{
    if (snake != NULL && snake->next != NULL)
        destroy_snake(snake->next);
    free(snake);
}

void snake_move(Snake *snake)
{
    if (snake == NULL)
        return;

    snake->pos.x = (snake->pos.x + snake->vel.x + FIELD_WIDTH) % FIELD_WIDTH;
    snake->pos.y = (snake->pos.y + snake->vel.y + FIELD_HEIGHT) % FIELD_HEIGHT;

    // correspond velocity to the next node
    if (snake->next == NULL)
        return;
    snake_move(snake->next);
    snake->next->vel.x = snake->vel.x;
    snake->next->vel.y = snake->vel.y;
}

bool snake_move_and_grow(Snake *snake)
{
    if (snake == NULL)
        return false;
    Snake *snake_tail = snake;
    for (; snake_tail->next != NULL; snake_tail = snake_tail->next)
    {
        // move forward towards the actual snake tail
    }

    Snake *new_node;

    if (!create_snake_node(&new_node,
                           snake_tail->pos.x,
                           snake_tail->pos.y,
                           snake_tail->vel.x,
                           snake_tail->vel.y))
        return false;

    snake_move(snake);

    snake_tail->next = new_node;
    return true;
}

bool change_vel(Snake *snake, SNAKE_VEL_STATE state)
{
    if (snake == NULL)
        return false;

    if (state == OFF)
        return true;

    int x = 0, y = 0;

    if (state == RIGHT)
        x += 1;
    else if (state == LEFT)
        x -= 1;
    // up and down is inverted, since (0, 0) is upper left
    else if (state == UP)
        y -= 1;
    else if (state == DOWN)
        y += 1;

    int old_x = snake->vel.x;
    int old_y = snake->vel.y;

    if (((old_x == -x) && old_x != 0) ||
        ((old_y == -y) && old_y != 0))
        return false;

    snake->vel.x = x;
    snake->vel.y = y;

    return true;
}
