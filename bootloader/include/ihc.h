#ifndef __IHC_H__
#define __IHC_H__

#include "macros.h"
#include "mem.h"
#include "syscalls.h"
#include "stdint.h"

extern unsigned long hart0ihczone;
static void* IHC_ZONE_START = &hart0ihczone;
static const unsigned long IHC_ZONE_SIZE = 1024;

void write_message(int hart, void* message, uint64_t bytes);
void read_message(int hart, void* dest, uint64_t bytes);

#endif