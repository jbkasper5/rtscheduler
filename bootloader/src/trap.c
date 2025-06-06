#include "trap.h"

extern void _infinite();

unsigned long traphandler(unsigned long mhartid, unsigned long mcause, unsigned long mepc){
    if(mhartid == 0){
        sched_trap(mcause, mepc);
    }else if(mhartid = 1){
        tm_trap(mcause, mepc);
    }
    return mepc;
}   

unsigned long sched_trap(unsigned long mcause, unsigned long mepc){
    if(mcause != TIMER_INTERRUPT){
        printf("Sched trap\n");
        printf("sched mcause: 0x%x\n", mcause);
        printf("sched mepc: 0x%x\n", mepc);
        _infinite();
    }
    scheduler_trap_handler();
    return mepc;
}

unsigned long tm_trap(unsigned long mcause, unsigned long mepc){
    // gracefully do nothing
    taskmanager_trap_handler();
    return mepc;
}