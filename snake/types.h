#ifndef TYPES_H
#define TYPES_H

typedef struct
{
    int x;
    int y;
} point_2d;


typedef struct Snake
{
    point_2d pos;
    point_2d vel;
    struct Snake *next;
} Snake;

#endif