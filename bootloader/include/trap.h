#include "print.h"

#define TIMER_INTERRUPT 0x8000000000000007
#define SW_INTERRUPT    0x8000000000000003

extern void scheduler_trap_handler();
extern void taskmanager_trap_handler();
extern void exit();

unsigned long traphandler(unsigned long mhartid, unsigned long mcause, unsigned long mepc);
unsigned long sched_trap(unsigned long mcause, unsigned long mepc);
unsigned long tm_trap(unsigned long mcause, unsigned long mepc);
