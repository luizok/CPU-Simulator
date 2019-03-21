#ifndef CPU_WORD_H
#define CPU_WORD

#include "headers.h"
#include "types.h"

typedef struct cpu_word {
    mem_addr_t  next_addr;
    jumpers_t   jump_flags;
    alu_t       alu;
    registers_t regs;
    //  B_bus;
} cpu_word_t;

#endif
