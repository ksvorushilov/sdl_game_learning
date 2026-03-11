#ifndef COLLISION_H
#define COLLISION_H

#include "manager.h"
#include "types.h"

typedef enum
{
    COLLISION_NONE,
    COLLISION_SELF,
    COLLISION_FOOD,
    COLLISION_BORDER

} COLLISION;

COLLISION collision_test(Game *game, point_2d *point);


#endif