#include "ihc.h"

void write_message(int hart, ihc_msg_t* message){
    void* addr = UNSCALED_POINTER_ADD(IHC_ZONE_START, (hart * IHC_ZONE_SIZE));
    memcpy(message, addr, sizeof(ihc_msg_t));
}

void read_message(int hart, ihc_msg_t* dest){
    void* addr = UNSCALED_POINTER_ADD(IHC_ZONE_START, (hart * IHC_ZONE_SIZE));
    memcpy(addr, dest, sizeof(ihc_msg_t));
}