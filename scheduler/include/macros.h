#ifndef __MACROS_H__
#define __MACROS_H__

#ifdef DEBUG
#define P(...) printf("DEBUG(%s, %s, %d) ", __FILE__, __FUNCTION__, __LINE__); printf(__VA_ARGS__);
#else
#define P(...)
#endif

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// used for malloc, makes arithmetic easier to read when computing heap addresses
#define UNSCALED_POINTER_ADD(x, y) ((void*)(((char*)(x)) + (y)))
#define UNSCALED_POINTER_SUB(x, y) ((void*)(((char*)(x)) - (y)))

#define ABS(x) ((x < 0) ? (-x) : (x))

// macro to perform a wait for interrupt instruction
#define WFI()       __asm__("wfi\n\t")

// use macros to replace some things from stdlib (true, false, NULL)
// also use macros in place of magic numbers to make relevant code more readable
#define TRUE            1
#define FALSE           0
#define NULL            0
#define TIME_UNIT       1000
#define IDLE            -1
#define UNSCHEDULABLE   -2

#define TIMEUNIT_TO_MS(timeunit) (timeunit * 1000)

#endif