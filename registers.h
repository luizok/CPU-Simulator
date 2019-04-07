#ifndef REGISTERS_H
#define REGISTERS_H

#define N_REGS 11

#define MDR    0b0000  // 0
#define PC     0b0001  // 1
#define MBR    0b0010  // 2
#define MBRU   0b0011  // 3
#define SP     0b0100  // 4
#define LV     0b0101  // 4
#define CPP    0b0110  // 6
#define TOS    0b0111  // 7
#define OPC    0b1000  // 8

#define MAR    0b1001  // 9
#define H      0b1010  // 10


void write_reg(int reg, int value);
int load_reg_in_bbus(int reg);

#endif