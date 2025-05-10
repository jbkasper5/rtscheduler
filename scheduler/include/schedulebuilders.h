#ifndef __SCHEDULEBUILDERS_H__
#define __SCHEDULEBUILDERS_H__

#include "macros.h"
#include "tasks.h"
#include "taskset.h"
#include "malloc.h"
#include "pq.h"

// takes in a pointer to a task and a int denoting the current timeunit
typedef int (*PRIORITY_FUNCTION)(task_t*, int);

int edf_priority_func(task_t* task, int timeunit);
int rm_priority_func(task_t* task, int timeunit);

int rm_least_upper_bound(taskset_t* taskset);
int rm_hyperbolic_bound(taskset_t* taskset);
int rm_response_time_analysis(taskset_t* taskset);

schedule_t* edf_scheduler(taskset_t* taskset);
schedule_t* rm_scheduler(taskset_t* taskset);
int schedule_task(int timeunit, pq_t* pq, taskset_t* taskset, PRIORITY_FUNCTION f);

long gcd(long a, long b);
long lcm(long a, long b);

#endif