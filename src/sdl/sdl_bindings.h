#ifndef SDL_BINDINGS_H
#define SDL_BINDINGS_H

#include <SDL2/SDL.h>
#include <stdint.h>

typedef enum
{
    ACTION_UP,
    ACTION_DOWN,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_ESC,
    ACTION_NONE
} action_enum_t;

typedef enum
{
    BIND_MENU,
    BIND_GAME
} bind_type_enum_t;

typedef struct
{
    SDL_Scancode key;
    action_enum_t action;

} key_bind_t;

static key_bind_t game_bind[] = {
    {SDL_SCANCODE_W, ACTION_UP},
    {SDL_SCANCODE_S, ACTION_DOWN},
    {SDL_SCANCODE_A, ACTION_LEFT},
    {SDL_SCANCODE_D, ACTION_RIGHT},
    {SDL_SCANCODE_UP, ACTION_UP},
    {SDL_SCANCODE_DOWN, ACTION_DOWN},
    {SDL_SCANCODE_LEFT, ACTION_LEFT},
    {SDL_SCANCODE_RIGHT, ACTION_RIGHT},
    {SDL_SCANCODE_UNKNOWN, -1}};

action_enum_t key_match(SDL_Scancode key, bind_type_enum_t bind_type);

#endif
