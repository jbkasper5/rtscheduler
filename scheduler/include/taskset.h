#ifndef __TASKSET_H__
#define __TASKSET_H__

#include "tasks.h"

task_t task1 = {
    .type = periodic,
    .execution_time = 1.0,
    .period = 5,
    .refresh = 0,
    .deadline = 10,
    .offset = 0
};

task_t task2 = {
    .type = periodic,
    .execution_time = 2.0,
    .period = 10,
    .refresh = 0,
    .deadline = 20,
    .offset = 3.0
};

taskset_t TaskSet = {
    .tasks = {&task1, &task2},
    .length = 2,
    .algorithm = EDF,
    .schedule = NULL,
    .schedulable = FALSE
};

#endif