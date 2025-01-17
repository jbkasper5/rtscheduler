#ifndef __MACROS_H__
#define __MACROS_H__

#ifdef DEBUG
#define P(...) printf("DEBUG(%s, %s, %d) ", __FILE__, __FUNCTION__, __LINE__); fflush(stdout); printf(__VA_ARGS__); fflush(stdout);
#else
#define P(...)
#endif

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define UNSCALED_POINTER_ADD(x, y) ((void*)((char*)x + y))
#define UNSCALED_POINTER_SUB(x, y) ((void*)((char*)x - y))

#define ABS(x) ((x < 0) ? (-x) : (x))

#define TRUE 1
#define FALSE 0
#define NULL 0

#define WFI()       __asm__("wfi\n\t")
#define PRINT_SP()  __asm__("mv a0, sp\n\t" "jal printl\n\t")

// each time unit is 500 ms (half a second) in this system
#define TIME_UNIT 1000

#endif