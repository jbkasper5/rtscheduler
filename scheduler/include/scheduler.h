#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "taskmanager.h"
#include "tasks.h"
#include "taskset.h"
#include "schedulebuilders.h"
#include "print.h"
#include "time.h"
#include "malloc.h"

void scheduler();
schedule_t* build_schedule(void);
extern void ping_taskmanager();

#endif