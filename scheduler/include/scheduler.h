#ifndef __HEADER_H__
#define __HEADER_H__
#include "tasks.h"
#endif


schedule_t* edf_scheduler(taskset_t* taskset);
schedule_t* rm_scheduler(taskset_t* taskset);