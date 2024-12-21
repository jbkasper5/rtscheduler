#ifndef __TASKSET_H__
#define __TASKSET_H__

#include "tasks.h"

static task_t task1 = {
    .type = periodic,
    .execution_time = 1.0,
    .period = 5,
    .refresh = 0,
    .deadline = 10,
    .offset = 0
};

static task_t task2 = {
    .type = periodic,
    .execution_time = 2.0,
    .period = 10,
    .refresh = 0,
    .deadline = 20,
    .offset = 3.0
};

static task_t* taskarr[] = {
    &task1,
    &task2
};

static taskset_t TaskSet = {
    .tasks = taskarr,
    .length = 2,
    .algorithm = RM,
    .schedule = NULL,
    .schedulable = FALSE
};

// static int sched[1000];

static schedule_t schedule = {
    // taken from slide 9 in FP lecture
    .schedule = NULL,
    .microcycles = 0,
    .macrocycles = 0,
};

#endif