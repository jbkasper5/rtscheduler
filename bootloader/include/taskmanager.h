#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

#include "print.h"
extern void lock_acquire();
extern void lock_release();
extern void wait_for_interrupt();

#endif