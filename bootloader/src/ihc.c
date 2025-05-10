#include "ihc.h"
#include "scheduler.h"
void write_message(int hart, void* message, uint64_t bytes){
    void* addr = UNSCALED_POINTER_ADD(IHC_ZONE_START, (hart * IHC_ZONE_SIZE));
    memcpy(message, addr, sizeof(scheduler_message_t));
}

void read_message(int hart, void* dest, uint64_t bytes){
    void* addr = UNSCALED_POINTER_ADD(IHC_ZONE_START, (hart * IHC_ZONE_SIZE));
    memcpy(addr, dest, sizeof(scheduler_message_t));
}