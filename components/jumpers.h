#ifndef JUMPERS_H
#define JUMPERS_H

#include "../types.h"

typedef struct jumpers {
    byte jmpc     : 1,
         jamn     : 1,
         jamz     : 1,
         reserved : 5;
} jumpers_t;

#endif
