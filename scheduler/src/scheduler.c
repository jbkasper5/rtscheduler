#include "scheduler.h"
#include "print.h"
#include "time.h"
#include "malloc.h"

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
    while(TRUE){
        WFI();
        ping_taskmanager();
        prints("Clock interrupt number ");
        printi(++num);
    }
}