#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "registers.h"
#include "cpu_word.h"
#include "firmware.h"


int main(int argc, char **argv) {

    init_firmware();

    printf("sizeof(cpu_word_t) = %d\n", (int) sizeof(cpu_word_t));
    cpu_word_t word = get_opcode(SUB);
    print_cpu_word(word);

    return EXIT_SUCCESS;
}
