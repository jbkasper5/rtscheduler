#ifndef __IPC_H__
#define __IPC_H__

const unsigned long IHC_ZONE_START = 0x8065414;
const unsigned long IHC_ZONE_SIZE = 0x400;
const unsigned long IHC_ZONE_END = 0x8066814;

enum MSG_TYPE{
    SEM_RELEASE,
    SEM_ACQUIRE,
    CHECKUP,
};

typedef struct MSG_s{
    char* msg;
    
} msg_t;

#endif