#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "registers.h"
#include "cpu_word.h"
#include "firmware.h"
#include "memory.h"

byte memory[MEM_LEN];

int main(int argc, char **argv) {

    init_firmware();
    // print_firmware();
    init_memory();
    // print_memory_until_byte(62);
    
    byte instruction;
    cpu_word_t running_instruction;
    byte file_size = size_of_file();
    // printf("File size: %u\n", file_size);
    for (size_t i = 0; i < file_size; i++) {
        instruction = memory[i+24];
        running_instruction = get_opcode(instruction);
    }
    

    return EXIT_SUCCESS;
}
