#ifndef FIRMWARE_H
#define FIRMWARE_H

#include "cpu_word.h"

#define FW_LEN 0x200
#define NOP    0x00
#define ADD    0x02
#define MOV    0x06
#define GOTO   0x09
#define JZ     0x0B
#define SUB    0x0D


void init_firmware(void);
cpu_word_t get_opcode(char opcode);
void print_firmware(void);

#endif