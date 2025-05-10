#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

// ensure uart is only defined in print.c
#ifndef __UART_DEF__
#define __UART_DEF__
static unsigned long* uart_addr = (unsigned long*)0x10010000;
#endif

#include "stdint.h"

extern unsigned int hartid();
extern void set_timer();
void sleep(uint64_t ms);
void putc(char c);
void getc(char* c);

#endif