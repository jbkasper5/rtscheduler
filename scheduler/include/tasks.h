#ifndef __TASK_H__
#define __TASK_H__

#include "macros.h"


enum Type{
    periodic,
    aperiodic,
    sporadic
};

enum Scheduler{
    EDF,                            // earliest deadline first
    RM                              // rate monotonic
};

typedef struct Task_s{
    enum Type type;               // task type, defined above
    int execution_time;           // execution time for the task
    int period;                   // period/mit for the task
    int refresh;                  // server refresh rate (if task is periodic server)
    int deadline;                 // task deadline
    int offset;                   // initial activation offset of the task
    int remaining_time            // time left in the tasks' execution
} task_t;

typedef struct TaskSet_s{
    struct Task_s** tasks;           // tasks 
    unsigned int length;            // number of tasks in the task set
    enum Scheduler algorithm;       // algorithm used to schedule the task set
    struct Schedule_s* schedule;    // if task set is schedulable, create a schedule
    unsigned char schedulable;      // flag, determines if the task set is schedulable
}taskset_t;

typedef struct Schedule_s{
    int* schedule;                  // array of ints, each index denotes which task is currently executing
    int len;                        // length of the schedule
    int microcycles;                // how ling each microcycle lasts
    int macrocycles;                // how long each macrocycle lasts
}schedule_t;


void print_task(task_t* task);

#endif