#include "taskmanager.h"
#include "print.h"
#include "time.h"

extern long printlock;

void task(unsigned long execution_time);

void tm_main(void){
    int val = -1;
    prints("&val = ");
    printl((long) &val);

    // local_time = pointer_sub(val - 8)
    while(1){
        // prints("Executing task...\n");
        task(100);
        // prints("Task execution complete.\n");
    }
    return;
}


// function to spin a task for it's execution time
void task(unsigned long execution_time){
    int start_time = mstime();
    prints("Task start time: ");
    printl(start_time);
    int curr_timeunit = 0;
    // while(mstime() < start_time + execution_time){
    while(1){
        wait_for_interrupt();
        curr_timeunit++;
        prints("TM time unit count: ");
        printi(curr_timeunit);
    }
}