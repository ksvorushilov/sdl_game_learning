
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include <ncurses.h>

#include "ui_and_engine.h"

uint32_t get_time_msec()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}
void time_delay(platform_timer_t val)
{
    napms(val); 
}
