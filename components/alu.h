#ifndef ALU_H
#define ALU

#include "../types.h"

typedef struct alu {
    byte inc  : 1,
         inva : 1,
         enb  : 1,
         ena  : 1,
         f_1  : 1,
         f_0  : 1,
         sra1 : 1,
         sll8 : 1;
} alu_t;

#endif
