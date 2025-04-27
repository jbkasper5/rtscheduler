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

void _prints(char* msg){
    *(uart_addr + 2) |= 1;
    *(uart_addr + 3) |= 1;
    while(*msg != '\0'){
        my_putchar(*msg);
        msg++;
    }
    return;
}

// doesn't handle negative numbers yet
char* int_to_str(int num, char is_long){
    char IS_NEGATIVE = FALSE;
    if(num < 0){
        IS_NEGATIVE = TRUE;
        num = (~num) + 1;
    }

    unsigned long size = is_long ? sizeof(long) * 8 : sizeof(int) * 8;
    char* str = malloc(size + 1);
    str[size] = '\0';
    int loc = size - 1;

    if(num == 0){
        str[loc--] = '0';
    }

    while(num){
        char val = num % 10;
        str[loc--] = '0' + num % 10;
        num /= 10;
    }

    if (IS_NEGATIVE) str[loc--] = '-';
    return (str + loc + 1);
}

void printf(char* format_str, ...){
    lock_acquire(&printlock);
    char* ptr = format_str;
    int nargs = 1;
    while(*ptr){
        if(*ptr == '%' && *(ptr + 1) != '%' && *(ptr + 1) != '\0') nargs++;
        ptr++;
    }

    // if no formats were specified, just print the string as normal
    if(nargs == 1){
        _prints(format_str);
        lock_release(&printlock);
        return;
    }

    va_list list;
    va_start(list, nargs);

    ptr = format_str;
    while(*ptr){
        if(*ptr == '%' && *(ptr + 1) != '%' && *(ptr + 1) != '\0'){
            char* str_conversion = NULL;
            switch (*(ptr + 1)){
                case 'd': 
                    str_conversion = int_to_str(va_arg(list, int), FALSE); break;
                case 'f':
                    // float -> die
                    break;
                case 's':
                    // string
                case 'c':
                    // char
                case 'x':
                    // hex
                case 'l':
                    str_conversion = int_to_str(va_arg(list, int), TRUE); break;
                default:
                    continue;
            }

            if(str_conversion){
                _prints(str_conversion);
                free(str_conversion);
            }
            ptr++;
        }else{
            my_putchar(*ptr);
        }
        ptr++;
    }
    va_end(list);
    lock_release(&printlock);
    return;
}