#include "print.h"

void my_putchar(char msg){
    *uart_addr = msg;
    return;
}

void my_getchar(char* c) {
    unsigned int value = *((unsigned int*) uart_addr + 1);
    while (value & 0x80000000) {
        value = *((unsigned int*) uart_addr + 1);
    }
    *c = value & 0xFF;
    return;
}

void prints(char* msg){
    *(uart_addr + 2) |= 1;
    *(uart_addr + 3) |= 1;
    while(*msg != '\0'){
        my_putchar(*msg);
        msg++;
    }
    return;
}

void printi(int msg){
    char str[INT_SIZE + 4] = "0b";
    str[INT_SIZE + 3] = '\0';
    str[INT_SIZE + 2] = '\n';
    for(int i = 0; i < INT_SIZE; ++i){
        str[INT_SIZE + 1 - i] = (msg & 0x1) ? '1' : '0';
        msg >>= 1;
    }
    prints(str);
    return;
}