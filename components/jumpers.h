#ifndef JUMPERS_H
#define JUMPERS_H

#include "../types.h"

typedef struct jumpers {
    byte jamz     : 1,
         jamn     : 1,
         jmpc     : 1,
         reserved : 5;
} jumpers_t;

#endif
