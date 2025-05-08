#include "syscalls.h"

void putc(char c){
    *uart_addr = c;
    return;
}

void getc(char* c) {
    unsigned int value = *((unsigned int*) uart_addr + 1);
    while (value & 0x80000000) {
        value = *((unsigned int*) uart_addr + 1);
    }
    *c = value & 0xFF;
    return;
}