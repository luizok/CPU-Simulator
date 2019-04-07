#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "registers.h"
#include "cpu_word.h"


int main(int argc, char *argv) {

    cpu_word_t word = WORD(011, 001010101, 11110010, 001111110, 110, 0101);

    printf("TAMAIN = %d\n", (int) sizeof(word));
    print_cpu_word(word);

    write_reg(H, 202);
    printf("MDR = %d\n", load_reg_in_bbus(H));

    return EXIT_SUCCESS;
}
