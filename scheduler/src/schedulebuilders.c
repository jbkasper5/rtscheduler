#include "schedulebuilders.h"
#include "print.h"
#include "macros.h"

// –––––––––––––––––––––– HELPER FUNCTIONS –––––––––––––––––––––– //
// perform the euclidean algorithm
long gcd(long a, long b){
    int div;
    int remainder = a;
    a = MAX(remainder, b);
    b = MIN(remainder, b);
    while(remainder){
        remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

long lcm(long a, long b){
    return (a * b / gcd(a, b));
}

int edf_priority_func(task_t* task, int timeunit){
    return (task->deadline + timeunit);
}

int rm_priority_func(task_t* task, int timeunit){
    return task->period;
}
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––– //


schedule_t* edf_scheduler(taskset_t* taskset) {
    schedule_t* schedule = (schedule_t*) malloc(sizeof(schedule_t));
    pq_t* pq = pq_init(taskset->length);

    pq_destroy(pq);
    return schedule;
}


schedule_t* rm_scheduler(taskset_t* taskset) {
    schedule_t* schedule = (schedule_t*) malloc(sizeof(schedule_t));
    pq_t* pq = pq_init(taskset->length);
    int curr_gcd, curr_lcm;

    if(taskset->length < 2){
        // gcd, lcm is just the one task
        curr_lcm = taskset->tasks[0]->period;
        curr_gcd = taskset->tasks[0]->period;
    }else{
        // get the baseline gcd and lcm of the first tasks
        curr_gcd = gcd(taskset->tasks[0]->period, taskset->tasks[1]->period);
        curr_lcm = lcm(taskset->tasks[0]->period, taskset->tasks[1]->period);
    }

    int newgcd, newlcm;
    for(int i = 0; i < taskset->length; i++){
        task_t* taskp = taskset->tasks[i];

        newgcd = gcd(curr_gcd, taskset->tasks[i]->period);
        if(newgcd > curr_gcd) curr_gcd = newgcd;

        newlcm = lcm(curr_lcm, taskset->tasks[i]->period);
        if(newlcm < curr_lcm) curr_lcm = newlcm;
    }

    int curr_timeunit = 0;
    schedule->macrocycles = curr_lcm;
    schedule->microcycles = curr_gcd;

    schedule->schedule = (int*)malloc(sizeof(int) * curr_lcm);
    if(!schedule->schedule){
        pq_destroy(pq);
        return NULL;
    }
    schedule->len = curr_lcm;


    // logic to actually build the schedule
    // populate every index in the schedule with the task that should run
    // -1 denotes CPU idle time
    int result;
    for(int i = 0; i < schedule->len; i++){
        result = schedule_task(curr_timeunit, pq, taskset, rm_priority_func);
        printf("Curr timeunit: %d\n", curr_timeunit);
        printf("Task to be scheduled: %d\n", result);

        // if we missed a deadline, destroy everything we malloc'd and return
        if(result == UNSCHEDULABLE){
            free(schedule->schedule);
            free(schedule);
            pq_destroy(pq);
            return NULL;
        }


        schedule->schedule[curr_timeunit] = result;
        // move onto the next time unit
        curr_timeunit++;
    }
    pq_destroy(pq);
    return schedule;
}

int schedule_task(int timeunit, pq_t* pq, taskset_t* taskset, PRIORITY_FUNCTION f){
    // step 1. Determine who enters the PQ (if anyone)
    for(int i = 0; i < taskset->length; i++){
        task_t* task = taskset->tasks[i];

        // task period expired, time to schedule it again
        if((timeunit - task->offset) % task->period == 0){
            // step 2. add to PQ (translating relative deadline to absolute)
            pq_add(pq, f(task, timeunit), task->execution_time, (task->deadline + timeunit), i);
        }
    }

    // step 3. get the task at the top of the PQ, should be -1 if PQ is empty
    pqnode_t* pq_head = peek(pq);
    if(!pq_head) return IDLE;

    // step 4. check the deadline (which is the PQ's priority)
    if(pq_head->deadline <= timeunit) return UNSCHEDULABLE;

    // step 5. age the task and figure out if it's done
    pq_head->remaining--;
    int task = pq_head->task;
    if(!pq_head->remaining) pop(pq);

    // return the task
    return task;
}