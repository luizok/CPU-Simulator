#ifndef REGISTERS_H
#define REGISTERS_H

#include "../types.h"

typedef struct registers {
    uint16_t unused : 7,
             h      : 1,
             opc    : 1,
             tos    : 1,
             cpp    : 1,
             lv     : 1,
             sp     : 1,
             pc     : 1,
             mdr    : 1,
             mar    : 1;
} registers_t;

#endif
