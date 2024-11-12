#ifndef __HEADER_H__ // If this is NOT defined
#define __HEADER_H__ // Define it for the first time

#include "tasks.h"

#endif // Toes protected


schedule_t* edf_scheduler(taskset_t* taskset);
schedule_t* rm_scheduler(taskset_t* taskset);