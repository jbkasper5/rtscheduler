#include "time.h"

unsigned long mstime(){
    // from the timer interrupt, 500*1047 is approximately 1 second between interrupts
    // since we want the time in millisecods, we divide by 1000, or estimate by left shifting by 1
    return (time() >> 10);
}