#include <stdlib.h>
#include <stdio.h>
#include "cpu_word.h"


cpu_word_t *new_cpu_word();
void print_cpu_word(cpu_word_t *cpu_w);

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

void print_cpu_word(cpu_word_t *cpu_w) {

    byte *word = (byte*) cpu_w;

    printf("JAM  NEXT_ADDR    ALU         C      MEM   B  \n");
    print_byte(word[0], 5, 7);
    printf("  ");
    print_byte(word[0], 8, 8);
    print_byte(word[1], 1, 8);
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
    hex_print(word, sizeof(cpu_word_t)-1);  // -1 because byte padding
    printf("\n");
}
