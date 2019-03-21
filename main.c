#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "cpu_word.h"


#define NEXT_ADDR_SIZE 9


void hex_print(byte *ptr, uint32_t n) {

    for(int i=0; i < n; i++) {
        if(i % 16 == 0) printf("\n");

        printf("%02X   ", ptr[i]);
    }
    printf("\n");
}

void print_word(cpu_word_t word) {

    printf("%d ", word.next_addr.upper);
    for(int i=NEXT_ADDR_SIZE-2; i >= 0; i--)
        printf("%d", (word.next_addr.addr >> i) & 0x01);

    printf("\n");
}


int main(int argc, char *argv) {

    cpu_word_t word;

    word.next_addr.upper = 0x00;
    word.next_addr.addr  = 0x0F;

    hex_print((byte*) &word, sizeof(word));
    print_word(word);

    return EXIT_SUCCESS;
}
