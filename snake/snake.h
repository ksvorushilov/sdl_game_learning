#ifndef SNAKE_H
#define SNAKE_H

#include "const.h"
#include "types.h"

bool create_snake_node(Snake **snake, int x, int y, int vel_x, int vel_y);
void destroy_snake(Snake *snake);
void move(Snake *snake);
bool move_and_grow(Snake *snake);
bool change_vel(Snake *snake, SNAKE_VEL_STATE state);
void generate_food(point_2d food[FOOD_QUANTITY], Snake *snake);



#endif