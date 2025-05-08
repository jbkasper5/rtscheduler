#include "mem.h"

void memcpy(void* src, void* dest, unsigned long bytes){
    unsigned long written = 0;
    char* srcptr = (char*)src;
    char* destptr = (char*)dest;
    while(written++ < bytes) *destptr++ = *srcptr++;
}

void memset(void* addr, char val, unsigned long bytes){
    unsigned long written = 0;
    char* ptr = (char*)addr;
    while(written++ < bytes) *ptr++ = val;
}
