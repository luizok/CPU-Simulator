#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "registers.h"
#include "cpu_word.h"
#include "firmware.h"
#include "memory.h"


int main(int argc, char **argv) {

//    init_firmware();
//    print_firmware();
    init_memory();
    print_memory_until_byte(70);

    return EXIT_SUCCESS;
}
