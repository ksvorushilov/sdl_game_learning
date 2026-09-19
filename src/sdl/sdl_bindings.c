#include <SDL2/SDL.h>
#include "sdl_bindings.h"

action_enum_t key_match(SDL_Scancode key, bind_type_enum_t bind_type)
{
    if (key == SDL_SCANCODE_UNKNOWN)
    {
        return ACTION_NONE;
    }
    key_bind_t *key_bind;
    if (bind_type == BIND_GAME)
    {
        key_bind = game_bind;
    }
    else
    {
        return ACTION_NONE;
    }

    while (key_bind->key != SDL_SCANCODE_UNKNOWN)
    {
        if (key == key_bind->key)
        {
            return key_bind->action;
        }
        key_bind++;
    }
    return ACTION_NONE;
}
