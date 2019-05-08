#ifndef FIRMWARE_H
#define FIRMWARE_H

#include "cpu_word.h"

#define FW_LEN          0x200
#define NOP             0x00
#define IADD            0x02
#define ISUB            0x05
#define IAND            0x08
#define IOR             0x0B
//#define DUP             0x0E
//#define POP             0x10
//#define SWAP            0x13
#define BIPUSH          0x19
#define ILOAD           0x1C
#define ISTORE          0x22
//#define WIDE            0x28
//#define LDC_W           0x32
//#define IINC            0x36
#define GOTO            0x3C
//#define IFLT            0x43
//#define IFEQ            0x47
#define IF_ICMPEQ       0x4B
//#define INVOKEVIRTUAL   0x55
//#define IRETURN         0x6B

void init_firmware(void);
cpu_word_t get_opcode(byte opcode);
void print_firmware(void);

#endif