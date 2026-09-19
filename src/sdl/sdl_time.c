#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#include "ui_and_engine.h"

uint32_t get_time_msec()
{
    return SDL_GetTicks();
}

void time_delay(platform_timer_t val)
{
    SDL_Delay(val);
}
