#include "malloc.h"

// perform math to get the next block in the heap
block_t* nextblock(block_t* block){
    block_t* next = UNSCALED_POINTER_ADD(block, (sizeof(blockheader_t) + ABS(block->info.size)));
    return (next > UNSCALED_POINTER_ADD(heap_start, heap_size)) ? NULL : next;
}

// search the heap for a free block of adequate size, no optimizations yet
block_t* search_heap(unsigned long request){
    long check_size = -request;
    if(heap_size == 0) return NULL;
    block_t* block = (block_t*)heap_start;
    while(block){
        if(block->info.size <= check_size) return block;
        block = nextblock(block);
    }
}

// allocate memory based on an aligned request size
void* malloc(unsigned long request){
    lock_acquire(&mlock);
    long int request_size = request;
    request_size = ALIGNMENT * ((request_size + ALIGNMENT - 1) / ALIGNMENT);
    block_t* block = search_heap(request_size);
    if(!block){        block = memsbrk(request_size + sizeof(blockheader_t));
        if(!block) return NULL;
        block->info.size = request_size;
        if(tail) tail->info.prev = block;
        tail = block;
    }
    block->info.size = ABS(block->info.size);
    lock_release(&mlock);
    return UNSCALED_POINTER_ADD(block, sizeof(blockheader_t));
}

// free memory previously allocated by malloc
void free(void* addr){
    lock_acquire(&mlock);
    block_t* block = UNSCALED_POINTER_SUB(addr, sizeof(blockheader_t));
    block->info.size = -block->info.size;
    lock_release(&mlock);
}

// sudo-syscall to expand the size of the heap
// uses the heap address defined in the bootloader to expand the heap
// prevents expansion beyond a maximum size, also predefined in the bootloader
void* memsbrk(unsigned long bytes){
    if(heap_size + bytes < MAX_HEAP_SIZE){
        void* addr = UNSCALED_POINTER_ADD(heap_start, heap_size);
        heap_size += bytes;
        return addr;
    }
    return NULL;
}