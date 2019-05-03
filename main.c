#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define uint16_t unsigned short int
#define uint32_t unsigned int
#define byte     unsigned char
#define WORD(J, A, ALU, C, M, B) new_cpu_word(0b##J##A##ALU##C##M##B)

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

#define FW_LEN 0x1FF
#define NOP    0x00
#define ADD    0x02
#define MOV    0x06
#define GOTO   0x09
#define JZ     0x0B
#define SUB    0x0D

typedef struct __attribute__((__packed__)) cpu_word {
    byte     high_addr : 1,
             jamz      : 1,
             jamn      : 1,
             jmpc      : 1,
             unused    : 4;
    byte     next_addr : 8;
    byte     inc       : 1,
             inva      : 1,
             enb       : 1,
             ena       : 1,
             f_1       : 1,
             f_0       : 1,
             sra1      : 1,
             sll8      : 1;
    uint16_t mdr       : 1,
             pc        : 1,
             sparc     : 1,
             lv        : 1,
             cpp       : 1,
             tos       : 1,
             opc       : 1,
             h         : 1,
             bbus      : 4,
             fetch     : 1,
             read      : 1,
             write     : 1,
             mar       : 1;
} cpu_word_t;

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


void hex_print(byte *ptr, uint32_t n) {

    for(int i=0; i < n; i++) {
        if(i != 0 && i % 16 == 0) printf("\n");

        printf("%02X  ", ptr[i]);
    }
    printf("\n");
}

void print_byte(byte b, byte from, byte to) {
    for(int i=8-from; i >= 8-to; i--)
        printf("%d", (b >> i) & 0x01);
}

void print_cpu_word(cpu_word_t cpu_w) {

    byte *word = (byte*) &cpu_w;

    printf("NEXT_ADDR  JAM  ALU         C        MEM   B  \n");
    print_byte(word[0], 8, 8);
    print_byte(word[1], 1, 8);
    printf("  ");
    print_byte(word[0], 5, 7);
    printf("  ");
    print_byte(word[2], 1, 8);
    printf("  ");
    print_byte(word[3], 1, 8);
    print_byte(word[4], 1, 1);
    printf("  ");
    print_byte(word[4], 2, 4);
    printf("  ");
    print_byte(word[4], 5, 8);

    printf("\t|\t");
    hex_print(word, sizeof(cpu_word_t));
    printf("\n");
}

cpu_word_t new_cpu_word(unsigned long bin) {

    char *w = (char*) calloc(sizeof(cpu_word_t), sizeof(char));
    char *bin_ref = (char*) &bin;

    if(bin)
        for(int i=0; i < 5; i++)
            memcpy(&w[4-i], &bin_ref[i], 1);

    return *(cpu_word_t*) w;
}

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
    // NOP | MAIN
    firmware[0x00] = WORD(100, 000000000, 00110101, 000000100, 001, 0001); // PC <- PC + 1; fetch; GOTO MBR;
    // TODO why skip address 0x01?
    // ADD OPC, mem[addr] | OPC <- OPC + mem[addr];
    firmware[0x02] = WORD(000, 000000011, 00110101, 000000100, 001, 0001); // PC <- PC + 1; fetch;
    firmware[0x03] = WORD(000, 000000100, 00010100, 000000001, 010, 0010); // MAR <- MBR; read;
    firmware[0x04] = WORD(000, 000000101, 00010100, 100000000, 000, 0000); // H <- MDR;
    firmware[0x05] = WORD(000, 000000000, 00111100, 010000000, 000, 1000); // OPC <- OPC + H; GOTO MAIN;

    // MOV OPC, mem[addr] | mem[addr] <- OPC;
    firmware[0x06] = WORD(000, 000000111, 00110101, 000000100, 001, 0001); // PC <- PC + 1; fetch;
    firmware[0x07] = WORD(000, 000001000, 00010100, 000000001, 000, 0010); // MAR <- MBR;
    firmware[0x08] = WORD(000, 000000000, 00010100, 000000010, 100, 1000); // MDR <- OPC; write; GOTO MAIN;

    // GOTO byte;
    firmware[0x09] = WORD(000, 000001010, 00110101, 000000100, 001, 0001); // PC <- PC + 1; fetch;
    firmware[0x0A] = WORD(100, 000000000, 00010100, 000000100, 001, 0010); // PC <- MBR; fetch; GOTO MBR;

    // JZ OPC, byte | if OPC = 0 GOTO addr else next_line
    firmware[0x0B] = WORD(001, 000001100, 00010100, 010000000, 000, 1000); // OPC <- OPC; IF ALU = 0 GOTO 268 (100001100) ELSE GOTO 12 (000001100);
    firmware[0x0C] = WORD(000, 000000000, 00110101, 000000100, 000, 0001); // PC <- PC + 1; GOTO MAIN;
    firmware[0x10C] = WORD(000, 100001101, 00110101, 000000100, 001, 0001); // PC <- PC + 1; fetch;
    firmware[0x10D] = WORD(100, 000000000, 00010100, 000000100, 001, 0010); // PC <- MBR; fetch; GOTO MBR;

    // OPC <- OPC - mem[addr];
    firmware[0x0D] = WORD(000, 000001110, 00110101, 000000100, 001, 0001); //PC <- PC + 1; fetch;
    firmware[0x0E] = WORD(000, 000001111, 00010100, 000000001, 010, 0010); //MAR <- MBR; read;
    firmware[0x0F] = WORD(000, 000010000, 00010100, 100000000, 000, 0000); //H <- MDR;
    firmware[0x10] = WORD(000, 000000000, 00111111, 010000000, 000, 1000); //OPC <- OPC - H; GOTO MAIN;

}

int main(int argc, char **argv) {

    init_firmware();

    FILE *fileRead = fopen("microprog.rom","rb");
    assert(fileRead);
    fread( firmware, sizeof(firmware[0]), 512, fileRead);
        
    
    fclose(fileRead);

    printf("sizeof(cpu_word_t) = %d\n", (int) sizeof(cpu_word_t));
    cpu_word_t word = get_opcode(ADD);
    print_cpu_word(word);

    FILE *fileWrite = fopen("microprog.rom","wb");
    assert(fileWrite);
    fwrite( firmware, sizeof(firmware[0]), 512, fileWrite);
    fclose(fileWrite);

    FILE *fileRead = fopen("microprog.rom","rb");
    assert(fileRead);
    fread( firmware, sizeof(firmware[0]), 512, fileRead);
    fclose(fileRead);

    return EXIT_SUCCESS;
}
