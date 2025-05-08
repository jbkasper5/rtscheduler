#include "scheduler.h"

schedule_t* build_schedule(void){
    taskset_t* set = &TaskSet;
    switch(set->algorithm){
        case EDF:
            printf("Building EDF schedule.\n");
            return edf_scheduler(&TaskSet);
        case RM:
            printf("Building RM schedule.\n");
            return rm_scheduler(&TaskSet);
        default:
            return NULL;
    }
}

void scheduler(){
    schedule_t* sched = build_schedule();
    if(!sched || !sched->schedule){
        printf("ERR: Taskset not schedulable. \n");
        return;
    }

    // will maintain the current index of the schedule
    int curr_timeunit = 0;
    printf("Beginning scheduling...\n");

    // will maintain clock times to determine if timeunits have passed
    unsigned long prev_time = mstime();
    unsigned long sched_curr_time;

    // IDLE is defined in macros.h
    unsigned int curr_running_task = IDLE;
    while(1){
        WFI();

        // once the scheduling process receives a timer interrupt, read the clock
        sched_curr_time = mstime();

        // determine whether or not a full timeunit has transpired
        // if it has, we need to see if a changed must be made to the current scheduled process
        if((sched_curr_time - prev_time) > TIME_UNIT){
            if(curr_timeunit % sched->len == 0 && curr_timeunit){

                // reset the state of the scheduler when a macrocycle completes
                printf("Schedule macrocycle complete.\n");
                curr_running_task = IDLE;
                curr_timeunit = 0;
            }
            if(sched->schedule[curr_timeunit] != curr_running_task){
                if(sched->schedule[curr_timeunit] == IDLE){
                    printf("Switching to IDLE.\n");
                }else{
                    printf("Switching to task %d\n", sched->schedule[curr_timeunit]);
                }
                curr_running_task = sched->schedule[curr_timeunit];
                ping_taskmanager();
            }else{
                printf("Continuing task...\n");
            }
            curr_timeunit++;
        }
    }
}