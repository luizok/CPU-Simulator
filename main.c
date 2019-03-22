#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "cpu_word.h"


#define NEXT_ADDR_SIZE 9
#define JUMP_SIZE      3


void hex_print(byte *ptr, uint32_t n) {

    for(int i=0; i < n; i++) {
        if(i != 0 && i % 16 == 0) printf("\n");

        printf("%02X  ", ptr[i]);
    }
    printf("\n");
}

void print_byte(byte b, byte bits) {
    for(int i=bits-1; i >= 0; i--)
        printf("%d", (b >> i) & 0x01);
}

void print_word_as_bytes(byte *word) {
    
    int n = sizeof(cpu_word_t)-1; // -1 because byte padding
    int sizes[] = {1, 8, 3, 8, 1, 8, 7};

    printf("NEXT_ADDR  JAM    ALU   /----C---\\ MEM B  \n");
    for(int i=0; i < n; i++) {
        print_byte(word[i], sizes[i]);
        printf(" ");
    }

    printf("\t|\t");
    hex_print(word, n);
    printf("\n");
}

void print_word(cpu_word_t word) {

    printf("%d ", word.next_addr.upper);
    for(int i=NEXT_ADDR_SIZE-2; i >= 0; i--)
        printf("%d", (word.next_addr.addr >> i) & 0x01);

    printf(" ");
    printf("%d", word.jump_flags.jmpc);
    printf("%d", word.jump_flags.jamn);
    printf("%d", word.jump_flags.jamz);
    printf(" ");

    printf("\n");
}


int main(int argc, char *argv) {

    cpu_word_t word;

    word.next_addr.upper = 0x01;
    word.next_addr.addr  = 0xF1;

    word.jump_flags.jmpc = 0x01;
    word.jump_flags.jamn = 0x01;
    word.jump_flags.jamz = 0x00;

    word.alu.f_1  = 1;
    word.alu.inva = 1;
    word.alu.inc  = 1;

    word.regs.h   = 1;
    word.regs.opc = 1;
    word.regs.tos = 1;
    word.regs.mar = 0;
    word.regs.mdr = 1;

    word.bus.write = 1;
    word.bus.read  = 1;
    word.bus.bus   = 0x0D;

    printf("TAMAIN = %d\n", sizeof(word));
    // print_word(word);
    print_word_as_bytes((byte*) &word);

    return EXIT_SUCCESS;
}
