#include <stdio.h>
#include <stdlib.h>
#include "registers.h"


int registers[N_REGS];

void write_reg(int reg, int value) {

    switch(reg) {
        case MAR: registers[MAR] = value; break;
        case MDR: registers[MDR] = value; break;
        case PC : registers[PC]  = value; break;
        case SP : registers[SP]  = value; break;
        case LV : registers[LV]  = value; break;
        case CPP: registers[CPP] = value; break;
        case TOS: registers[TOS] = value; break;
        case OPC: registers[OPC] = value; break;
        case H  : registers[H]   = value; break;
        default : printf("Unabled to write in %d\n", reg); break;
    }
}

int load_reg_in_bbus(int reg) {

    switch(reg) {
        case MDR : return registers[MDR];
        case PC  : return registers[PC];
        case MBR : return registers[MBR];
        case MBRU: return registers[MBRU];
        case SP  : return registers[SP];
        case LV  : return registers[LV];
        case CPP : return registers[CPP];
        case TOS : return registers[TOS];
        case OPC : return registers[OPC];
        default  : printf("Unabled to load from %d\n", reg); break;
    }
}