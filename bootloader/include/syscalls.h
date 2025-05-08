#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

extern unsigned int hartid();

// ensure uart is only defined in print.c
#ifndef __UART_DEF__
#define __UART_DEF__
static unsigned long* uart_addr = (unsigned long*)0x10010000;
#endif

extern unsigned int hartid();
void putc(char c);
void getc(char* c);

#endif