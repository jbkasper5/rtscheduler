#include "scheduler.h"
#include "print.h"
#include "time.h"

extern void wait_for_interrupt();
extern void ping_taskmanager();

void build_schedule(void){
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

int sched_curr_time = 0;
int curr_running_task = -2;
int passed_timeunits = 0;
int prev_timeunit = 0;

static int dummy_schedule[] = {0, 1, 2, 2, 0, 2, 1, 2, 0, 2, 2, -1, -2};
int dummy_sched_len = 12;
void scheduler(){
    // build_schedule();

    // get current time in milliseconds
    prev_timeunit = mstime();
    curr_running_task = dummy_schedule[passed_timeunits];
    while(1){
        wait_for_interrupt();
        sched_curr_time = mstime();

        // one time unit has transpired
        if((sched_curr_time - prev_timeunit) > TIME_UNIT){
            if(dummy_schedule[passed_timeunits] == -2){
                prints("Schedule macrocycle complete.\n");
                curr_running_task = dummy_schedule[0];
                passed_timeunits = 0;
                continue;
            }
            if(dummy_schedule[passed_timeunits] != curr_running_task){
                prints("Time unit elapsed! Switching to task ");
                printi(dummy_schedule[passed_timeunits]);
                curr_running_task = dummy_schedule[passed_timeunits];
            }else{
                prints("Continuing execution of task ");
                printi(curr_running_task);
            }
            prev_timeunit = sched_curr_time;
            passed_timeunits++;
        }
    }
    return;
}