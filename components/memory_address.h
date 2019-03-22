#ifndef MEM_ADDR_H
#define MEM_ADDR_H

#include "../types.h"

typedef struct memory_address {
    uint16_t upper    : 1, // UNUSED
             unused   : 7,  // if upper is true { addr = addr } else { addr = 0x100 + addr }
             addr     : 8;  // 0x00 <= addr <= 0xFF
} mem_addr_t;

#endif
