#include "schedulebuilders.h"
#include "scheduler.h"

// defines TaskSet
#include "taskset.h"

int main(int argc, char** argv){
    taskset_t* set = &TaskSet;
    int schedulable = rm_least_upper_bound(set);
    P("LUB test: %d\n", schedulable);
    for(int i = 0; i < set->length; i++){
        print_task(set->tasks[i]);
    }
    schedule_t* schedule = edf_scheduler(set);
    scheduler();
    return 0;
}