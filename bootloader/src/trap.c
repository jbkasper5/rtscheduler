#include "trap.h"

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
        prints("Sched trap\n");
        prints("sched mcause: ");
        printl(mcause);
        prints("sched mepc: ");
        printl(mepc);
    }
    scheduler_trap_handler();
    return mepc;
}

unsigned long tm_trap(unsigned long mcause, unsigned long mepc){
    // gracefully do nothing
    if(mcause != SW_INTERRUPT){
        prints("TM trap\n");
        prints("tm mcause: ");
        printl(mcause);
        prints("tm mepc: ");
        printl(mepc);
    }
    taskmanager_trap_handler();
    return mepc;
}