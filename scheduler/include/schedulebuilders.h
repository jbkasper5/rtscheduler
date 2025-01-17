#ifndef __SCHEDULEBUILDERS_H__
#define __SCHEDULEBUILDERS_H__

#include "macros.h"
#include "tasks.h"
#include "taskset.h"
#include "malloc.h"
#include "pq.h"

int rm_least_upper_bound(taskset_t* taskset);
int rm_hyperbolic_bound(taskset_t* taskset);
int rm_response_time_analysis(taskset_t* taskset);

schedule_t* edf_scheduler(taskset_t* taskset);
schedule_t* rm_scheduler(taskset_t* taskset);

#endif