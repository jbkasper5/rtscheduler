#include "scheduler.h"
#include "print.h"
#include "time.h"

extern void wait_for_interrupt();
extern void ping_taskmanager();
extern long printlock;

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
    int local_time = mstime();
    prints("Local time: ");
    printi(local_time);
    int previous_time = local_time;
    prints("previous_time: ");
    printi(previous_time);
    while(1){
        wait_for_interrupt();
        local_time = mstime();
        prints("Local time: ");
        printl(local_time);
        prints("Previous time: ");
        printl(previous_time);
        if(local_time - previous_time > TIME_UNIT){
            prints("Pinging taskmanager...\n");
            ping_taskmanager();
            previous_time = local_time;
        }
    }
    return;
}