#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

#include "print.h"
#include "time.h"
#include "malloc.h"
#include "ihc.h"
#include "syscalls.h"


void task(unsigned long execution_time);
void tm_main();

#endif