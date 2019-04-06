#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "cpu_word.h"


int main(int argc, char *argv) {

    cpu_word_t *word = (cpu_word_t*) calloc(1, sizeof(cpu_word_t));

    word->unused = 0;

    word->jmpc = 1;
    word->jamn = 0;
    word->jamz = 1;

    word->high_addr = 1;
    word->next_addr  = 0b10101010;

    word->f_1 = 1;
    word->inc = 1;

    word->h = 1;
    word->opc = 1;
    word->mar = 1;

    word->fetch = 1;

    word->regs = 0b1011;

    printf("TAMAIN = %d\n", (int) sizeof(*word));
    print_cpu_word(word);

    return EXIT_SUCCESS;
}
