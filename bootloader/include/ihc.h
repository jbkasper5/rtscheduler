#ifndef __IHC_H__
#define __IHC_H__

#include "macros.h"
#include "mem.h"
#include "syscalls.h"

extern unsigned long hart0ihczone;
static void* IHC_ZONE_START = &hart0ihczone;
static const unsigned long IHC_ZONE_SIZE = 1024;

typedef struct ICH_MSG_s{
    char data[1024];
} ihc_msg_t;

void write_message(int hart, ihc_msg_t* message);
void read_message(int hart, ihc_msg_t* dest);

#endif