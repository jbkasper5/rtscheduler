#include "scheduler.h"

void scheduler(void){
    taskset_t* set = &TaskSet;
    switch(set->algorithm){
        case EDF:
            edf_scheduler(set); break;
        case RM:
            rm_scheduler(set); break;
        default:
            break;
    }
    // trigger task manager interrupt

    return;
}