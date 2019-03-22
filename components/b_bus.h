#ifndef B_BUS_H
#define B_BUS_H

#include "../types.h"

typedef struct b_bus {
    byte bus    : 4,
         fetch  : 1,
         read   : 1,
         write  : 1,
         unused : 1;
} bbus_t;

#endif
