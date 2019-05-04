#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "firmware.h"
#include "cpu_word.h"
#include "types.h"


cpu_word_t firmware[0x200];


cpu_word_t get_opcode(char opcode) {

    switch(opcode) {
        case NOP : return firmware[NOP];
        case ADD : return firmware[ADD];
        case MOV : return firmware[MOV];
        case GOTO: return firmware[GOTO];
        case JZ  : return firmware[JZ];
        case SUB : return firmware[SUB];
        default: printf("Invalid OPCODE = 0x%03X\n", opcode);
    }
}

void init_firmware(void) {
/*  // NOP | MAIN
    firmware[0x00] = WORD(100, 000000000, 00110101, 000000100, 001, 0001); // PC <- PC + 1; fetch; GOTO MBR;
    // TODO why skip address 0x01?
    // ADD OPC, mem[addr] | OPC <- OPC + mem[addr];
    firmware[0x02] = WORD(000000011, 000, 00110101, 000000100, 001, 0001); // PC <- PC + 1; fetch;
    firmware[0x03] = WORD(000000100, 000, 00010100, 000000001, 010, 0010); // MAR <- MBR; read;
    firmware[0x04] = WORD(000000101, 000, 00010100, 100000000, 000, 0000); // H <- MDR;
    firmware[0x05] = WORD(000000000, 000, 00111100, 010000000, 000, 1000); // OPC <- OPC + H; GOTO MAIN;

    // MOV OPC, mem[addr] | mem[addr] <- OPC;
    firmware[0x06] = WORD(000000111, 000, 00110101, 000000100, 001, 0001); // PC <- PC + 1; fetch;
    firmware[0x07] = WORD(000001000, 000, 00010100, 000000001, 000, 0010); // MAR <- MBR;
    firmware[0x08] = WORD(000000000, 000, 00010100, 000000010, 100, 1000); // MDR <- OPC; write; GOTO MAIN;

    // GOTO byte;
    firmware[0x09] = WORD(000001010, 000, 00110101, 000000100, 001, 0001); // PC <- PC + 1; fetch;
    firmware[0x0A] = WORD(000000000, 100, 00010100, 000000100, 001, 0010); // PC <- MBR; fetch; GOTO MBR;

    // JZ OPC, byte | if OPC = 0 GOTO addr else next_line
    firmware[0x0B] = WORD(000001100, 001, 00010100, 010000000, 000, 1000); // OPC <- OPC; IF ALU = 0 GOTO 268 (100001100) ELSE GOTO 12 (000001100);
    firmware[0x0C] = WORD(000000000, 000, 00110101, 000000100, 000, 0001); // PC <- PC + 1; GOTO MAIN;
    firmware[0x10C] = WORD(100001101, 000, 00110101, 000000100, 001, 0001); // PC <- PC + 1; fetch;
    firmware[0x10D] = WORD(000000000, 100, 00010100, 000000100, 001, 0010); // PC <- MBR; fetch; GOTO MBR;

    // OPC <- OPC - mem[addr];
    firmware[0x0D] = WORD(000, 000001110, 00110101, 000000100, 001, 0001); //PC <- PC + 1; fetch;
    firmware[0x0E] = WORD(000, 000001111, 00010100, 000000001, 010, 0010); //MAR <- MBR; read;
    firmware[0x0F] = WORD(000, 000010000, 00010100, 100000000, 000, 0000); //H <- MDR;
    firmware[0x10] = WORD(000, 000000000, 00111111, 010000000, 000, 1000); //OPC <- OPC - H; GOTO MAIN;
*/
    execl("/usr/bin/python3", "/usr/bin/python3", "main.py", NULL);

    unsigned long array[512];
    FILE *file = fopen("microprog.rom","rb");
    assert(file);
    fread( array, sizeof(array[0]), 512, file);

    for(int i = 0; i < 512; i++)
    {
        firmware[i] = new_cpu_word(array[i]);
    }

    fclose(file);

    // /*printf("printando 20 primeiros binarios em firmware:\n");
    for(int i = 0; i < 20; i++)
    {
        print_cpu_word(firmware[i]);
    }
    
}