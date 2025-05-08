#include "print.h"

char nibble_to_char(char nibble){
    switch(nibble){
        case 0 ... 9:
            return '0' + nibble;
        case 10 ... 15:
            return 'A' + (nibble - 10);
    }
}

void _prints(char* msg){
    *(uart_addr + 2) |= 1;
    *(uart_addr + 3) |= 1;
    while(*msg != '\0'){
        putc(*msg);
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

char* to_hex_str(unsigned long num){
    unsigned long size = sizeof(void*);
    char* str = malloc(size + 1);
    str[size] = '\0';
    int loc = size - 1;

    if(num == 0){
        str[loc--] = '0';
    }

    while(num){
        str[loc--] = nibble_to_char(num & 0xF);
        num >>= 4;
    }
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
                case 's':
                    str_conversion = va_arg(list, char*);
                    _prints(str_conversion);
                    ptr += 2;
                    continue;
                case 'c':
                    // char c = va_arg(list, char);
                    // putc(c); 
                    break;
                case 'x':
                    str_conversion = to_hex_str(va_arg(list, unsigned long)); break;
                case 'l':
                    str_conversion = int_to_str(va_arg(list, long), TRUE); break;
                default:
                    break;
            }

            if(str_conversion){
                _prints(str_conversion);
                free(str_conversion);
            }
            ptr++;
        }else{
            putc(*ptr);
        }
        ptr++;
    }
    va_end(list);
    lock_release(&printlock);
    return;
}