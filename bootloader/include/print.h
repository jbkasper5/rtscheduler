#ifndef __PRINT_H__
#define __PRINT_H__

// ensure uart is only defined in print.c
#ifndef __UART_DEF__
#define __UART_DEF__
static unsigned long* uart_addr = (unsigned long*)0x10010000;
#endif

void prints(char* msg);
void printi(int msg);
void my_getchar(char* c);
void my_putchar(char msg);

extern void lock_acquire();
extern void lock_release();

#define INT_SIZE 32

#endif