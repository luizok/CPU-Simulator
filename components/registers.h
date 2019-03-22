#ifndef REGISTERS_H
#define REGISTERS_H

#include "../types.h"

typedef struct registers {
//    uint16_t mar    : 1,
//             mdr    : 1,
//             pc     : 1,
//             sp     : 1,
//             lv     : 1,
//             cpp    : 1,
//             tos    : 1,
//             opc    : 1,
//             h      : 1,
//             unused : 7;
    uint16_t h      : 1,
             unused : 7,
             mar    : 1,
             mdr    : 1,
             pc     : 1,
             sp     : 1,
             lv     : 1,
             cpp    : 1,
             tos    : 1,
             opc    : 1;
} registers_t;

#endif
