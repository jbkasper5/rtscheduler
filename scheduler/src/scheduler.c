#include "scheduler.h"

schedule_t* build_schedule(void){
    taskset_t* set = &TaskSet;
    switch(set->algorithm){
        case EDF:
            prints("Building EDF schedule.\n");
            return edf_scheduler(set);
        case RM:
            prints("Building RM schedule.\n");
            return rm_scheduler(set);
        default:
            return NULL;
    }
}

void scheduler(){
    schedule_t* sched = build_schedule();
    int curr_timeunit = 0;
    prints("Beginning scheduling...\n");
    while(1){
        WFI();
        prints("Sending ping...\n");
        // ping_taskmanager();

        // increment the current timeunit to align with the schedule
        curr_timeunit++;
    }
}