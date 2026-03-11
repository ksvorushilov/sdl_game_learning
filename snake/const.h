#ifndef CONST_H
#define CONST_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define FIELD_SCALE 20

#define FIELD_WIDTH (SCREEN_WIDTH / FIELD_SCALE)
#define FIELD_HEIGHT (SCREEN_HEIGHT / FIELD_SCALE)

#define FPS 60
#define FRAME_TIME (1000 / FPS)

#define INIT_SNAKE_SPEED 600

#define PROJECT_PIXEL_FORMAT SDL_PIXELFORMAT_RGBA8888

#define FOOD_QUANTITY 3

#define SPRITE_ADDRESS "sprite.bmp"

typedef enum VEL_STATE
{
    OFF,
    UP,
    DOWN,
    LEFT,
    RIGHT,
} SNAKE_VEL_STATE;

static const  char WINDOW_TITLE[] = "Snake Game";


#endif