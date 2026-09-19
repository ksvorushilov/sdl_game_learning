#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "manager.h"

void game_input(struct Game_t *game);
void game_update(struct Game_t *game);
void game_render(struct Game_t *game);

#endif
