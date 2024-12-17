#include "scheduler.h"

void scheduler(){
    taskset_t* set = &TaskSet;
    switch(TaskSet.algorithm){
        case EDF:
            edf_scheduler(set); break;
        case RM:
            rm_scheduler(set); break;
        default:
            break;
    }
    return;
}