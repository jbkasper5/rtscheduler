#include "scheduler.h"
#include "print.h"
#include "time.h"
#include "malloc.h"

extern void wait_for_interrupt();
extern void ping_taskmanager();

void build_schedule(void){
    taskset_t* set = &TaskSet;
    switch(set->algorithm){
        case EDF:
            prints("Building EDF schedule.\n");
            edf_scheduler(set); break;
        case RM:
            prints("Building RM schedule.\n");
            rm_scheduler(set); break;
        default:
            break;
    }
    // trigger task manager interrupt

    return;
}

void scheduler(){
    int num = 0;
    // ping_taskmanager();
    while(TRUE){
        // ping_taskmanager();
        prints("Iteration ");
        printi(num);
        wait_for_interrupt();
        prints("Scheduler returned from WFI.\n");
        ping_taskmanager();
        num++;
    }
}