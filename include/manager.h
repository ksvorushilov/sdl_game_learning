#ifndef MANAGER_H
#define MANAGER_H

#include <stdbool.h>

#include "const.h"
#include "types.h"

void game_cleanup(struct Game_t *game);
bool game_initialise(struct Game_t *game);

#endif
