#include "print.h"

char nibble_to_char(char nibble){
    switch(nibble){
        case 0:
            return '0';
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            return '1' + (nibble - 1);
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            return 'A' + (nibble - 10);
    }
}

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

void printh(int msg){
    int strsize = INT_SIZE / 8;
    char str[INT_SIZE / 8 + 4] = "0x";
    str[strsize + 3] = '\0';
    str[strsize + 2] = '\n';
    for(int i = 0; i < strsize; ++i){
        str[strsize + 1 - i] = nibble_to_char(msg & 0xF);
        msg >>= 4;
    }
    prints(str);
    return;
}