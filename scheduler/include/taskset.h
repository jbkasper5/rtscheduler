#ifndef __TASKSET_H__
#define __TASKSET_H__

#include "tasks.h"

static task_t task1 = {
    .type = periodic,
    .execution_time = 1,
    .period = 5,
    .refresh = 0,
    .deadline = 4,
    .offset = 1,
    .remaining_time = 1
};

static task_t task2 = {
    .type = periodic,
    .execution_time = 2,
    .period = 10,
    .refresh = 0,
    .deadline = 5,
    .offset = 0,
    .remaining_time = 2
};

static task_t* taskarr[] = {
    &task1,
    &task2
};

static taskset_t TaskSet = {
    .tasks = taskarr,
    .length = 2,
    .algorithm = EDF,
    .schedule = NULL,
    .schedulable = FALSE
};

#endif