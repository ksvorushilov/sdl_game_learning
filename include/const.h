#ifndef CONST_H
#define CONST_H

#include <stdbool.h>
#include <time.h>

#define FIELD_WIDTH 40
#define FIELD_HEIGHT 30

#define FPS 60
// very imprecise. nobody cares, it's a snake, not doom
#define FRAME_TIME (1000 / FPS) // clocks per sec can be remapped for sdl implementation

#define INIT_SNAKE_STEP_TIME 300

#define FOOD_QUANTITY 3

typedef enum VEL_STATE
{
    OFF,
    UP,
    DOWN,
    LEFT,
    RIGHT,
} SNAKE_VEL_STATE;

static const char WINDOW_TITLE[] = "Snake Game";

#endif
