#ifndef TYPES_H // This is called include guard
#define TYPES_H // and it is a standard C idiom for header files

// typedef char *string // conflicting with const modifier in function prototype
#include <inttypes.h>

typedef struct
{
    int x;
    int y;
} point_2d;

#endif // end of include guard