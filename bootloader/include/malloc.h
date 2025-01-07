#ifndef __MALLOC_H__
#define __MALLOC_H__

#include "macros.h"
#include "print.h"

typedef struct freeblockheader_s{
    struct freeblockheader_t* nextfree;
    struct freeblockheader_t* prevfree;
} freeblockheader_t;

typedef struct blockheader_s{
    long size;
    struct block_s* prev;
} blockheader_t;

typedef struct block_s{
    blockheader_t info;
    freeblockheader_t freeinfo;
} block_t;



extern long mlock;
extern long heap;
static void* heap_start = &heap;
static unsigned long heap_size = 0;
static block_t* tail = NULL;

// max heap size is 32 KiB, as defined in the bootloader
#define MAX_HEAP_SIZE 32768
#define ALIGNMENT (sizeof(freeblockheader_t))

extern void lock_acquire(void* lock);
extern void lock_release(void* lock);

block_t* nextblock(block_t* block);
block_t* search_heap(unsigned long request);
void* malloc(unsigned long request);
void free(void* addr);
void* memsbrk(unsigned long bytes);


#endif