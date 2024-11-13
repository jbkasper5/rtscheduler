#include <stdlib.h>
#include <stdio.h>

#ifndef __MACRO_H__
#define __MACRO_H__
#include "macros.h"
#endif


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
    enum Type type;                 // task type, defined above
    float execution_time;           // execution time for the task
    float period;                   // period/mit for the task
    float refresh;                  // server refresh rate (if task is periodic server)
    float deadline;                 // task deadline
    float offset;                   // initial activation offset of the task
    // float priority;                 // task priority (changes based on scheduling algorithm)
} task_t;

typedef struct TaskSet_s{
    struct Task_s* tasks;           // tasks 
    unsigned int length;            // number of tasks in the task set
    enum Scheduler algorithm;       // algorithm used to schedule the task set
    struct Schedule_s* schedule;    // if task set is schedulable, create a schedule
    unsigned char schedulable;      // flag, determines if the task set is schedulable
}taskset_t;

typedef struct Schedule_s{
    int* schedule;                  // array of ints, each index denotes which task is currently executing
    int microcycles;                // how ling each microcycle lasts
    int macrocycles;                // how long each macrocycle lasts
}schedule_t;


void print_task(task_t* task);
taskset_t* taskset_init(int num_tasks);
schedule_t* schedule_init();

void taskset_destroy(taskset_t* taskset);
void schedule_destroy(schedule_t* schedule);