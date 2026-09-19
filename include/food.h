#ifndef FOOD_H
#define FOOD_H

#include "manager.h"

void food_generate(Game_t *game);
void food_reroll_by_value(const point_2d *value, Game_t *game);
void food_reroll_instance(size_t i, Game_t *game);

#endif
