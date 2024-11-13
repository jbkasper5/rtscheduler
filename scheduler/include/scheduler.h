#include <math.h>

#ifndef __HEADER_H__
#define __HEADER_H__
#include "tasks.h"
#endif

int rm_least_upper_bound(taskset_t* taskset);
int rm_hyperbolic_bound(taskset_t* taskset);
int rm_response_time_analysis(taskset_t* taskset);

schedule_t* edf_scheduler(taskset_t* taskset);
schedule_t* rm_scheduler(taskset_t* taskset);