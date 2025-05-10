#include "syscalls.h"
#include "macros.h"

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

// sleep a task for some number of MS
// NOTE: can only be invoked by non-scheduler harts
void sleep(uint64_t ms){
    // rough conversion to ms in machine clock cycle time
    set_timer(hartid(), ms * 1000);
}