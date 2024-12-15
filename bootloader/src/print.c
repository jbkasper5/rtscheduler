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
    lock_acquire();
    *(uart_addr + 2) |= 1;
    *(uart_addr + 3) |= 1;
    while(*msg != '\0'){
        my_putchar(*msg);
        msg++;
    }
    lock_release();
    return;
}

void printi(int msg){
    int strsize = INT_SIZE / 4;
    char str[INT_SIZE / 4 + 4] = "0x";
    str[strsize + 3] = '\0';
    str[strsize + 2] = '\n';
    for(int i = 0; i < strsize; ++i){
        str[strsize + 1 - i] = nibble_to_char(msg & 0xF);
        msg >>= 4;
    }
    prints(str);
    return;
}

void printf(float f){
    int strsize = FLOAT_SIZE / 4;
    char str[FLOAT_SIZE / 4 + 4] = "0x";
    str[strsize + 3] = '\0';
    str[strsize + 2] = '\n';
    int msg = *(int*)&f;
    for(int i = 0; i < strsize; ++i){
        str[strsize + 1 - i] = nibble_to_char(msg & 0xF);
        msg >>= 4;
    }
    prints(str);
}

void printl(long msg){
    int strsize = LONG_SIZE / 4;
    char str[LONG_SIZE / 4 + 4] = "0x";
    str[strsize + 3] = '\0';
    str[strsize + 2] = '\n';
    for(int i = 0; i < strsize; ++i){
        str[strsize + 1 - i] = nibble_to_char(msg & 0xF);
        msg >>= 4;
    }
    prints(str);
    return;
}