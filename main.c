#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "registers.h"
#include "cpu_word.h"
#include "firmware.h"


int main(int argc, char **argv) {

    init_firmware();
    print_firmware();

    return EXIT_SUCCESS;
}
