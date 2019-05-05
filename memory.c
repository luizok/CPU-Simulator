#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "memory.h"
#include "types.h"
#include "cpu_word.h"

byte memory[MEM_LEN];

void init_memory(void){
    FILE *file_memory = fopen("prog.exe","rb");
    assert(file_memory);
    fread( memory, sizeof(memory[0]), MEM_LEN, file_memory);
    fclose(file_memory);
}

void print_memory_until_byte(int len){
    for(int i = 0; i < len; i++) {
        printf("0x%02x\t", memory[i]);
        print_byte(memory[i], 1, 8);
        printf("\n");
    } 
}

void print_memory(void){
    print_memory_until_byte(MEM_LEN);
}
