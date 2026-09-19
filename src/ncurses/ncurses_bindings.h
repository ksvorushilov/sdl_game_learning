#ifndef NCURSES_BINDINGS_H
#define NCURSES_BINDINGS_H

#include <stdint.h>

#include <ncurses.h>

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
    int32_t key;
    action_enum_t action;

} key_bind_t;

static key_bind_t game_bind[] = {
    {'w', ACTION_UP},
    {'s', ACTION_DOWN},
    {'a', ACTION_LEFT},
    {'d', ACTION_RIGHT},
    {KEY_UP, ACTION_UP},
    {KEY_DOWN, ACTION_DOWN},
    {KEY_LEFT, ACTION_LEFT},
    {KEY_RIGHT, ACTION_RIGHT},
    {ERR, -1}};

action_enum_t key_match(int32_t key, bind_type_enum_t bind_type);

#endif
