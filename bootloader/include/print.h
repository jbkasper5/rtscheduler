#ifndef __PRINT_H__
#define __PRINT_H__

// ensure uart is only defined in print.c
#ifndef __UART_DEF__
#define __UART_DEF__
static unsigned long* uart_addr = (unsigned long*)0x10010000;
#endif

char nibble_to_char(char nibble);
void my_getchar(char* c);
void my_putchar(char msg);

void prints(char* msg);
void printi(int msg);
void printl(long msg);
void printf(float f);
void printaddr(long msg);

extern long printlock;
extern void lock_acquire(void* lock);
extern void lock_release(void* lock);

#define INT_SIZE    (sizeof(int) * 8)
#define FLOAT_SIZE  (sizeof(float) * 8)
#define LONG_SIZE   (sizeof(long) * 8)

#endif