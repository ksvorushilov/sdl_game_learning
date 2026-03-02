#ifndef TYPES_H // This is called include guard
#define TYPES_H // and it is a standard C idiom for header files

// typedef char *string // conflicting with const modifier in function prototype
#include <inttypes.h>

typedef struct
{
    uint32_t x;
    uint32_t y;
} point_2d;

#endif // end of include guard