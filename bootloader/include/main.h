#ifndef __MAIN_H__
#define __MAIN_H__

#include "print.h"
extern void lock_acquire();
extern void lock_release();
extern void wait_for_interrupt();

extern void ping_taskmanager();

void taskmanager_checkup();
#endif