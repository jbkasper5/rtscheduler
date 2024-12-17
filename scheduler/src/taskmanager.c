#include "taskmanager.h"
#include "print.h"
#include "time.h"

void task(unsigned long execution_time);

void tm_main(void){
    prints("Hello from tm_main!\n");
    while(1){
        task(100);
    }
    return;
}


int curr_timeunit = 0;
int start_time = 0;

// function to spin a task for it's execution time
void task(unsigned long execution_time){
    start_time = mstime();
    prints("Start time: ");
    printi(start_time);
    while(mstime() < start_time + execution_time){
        wait_for_interrupt();
        curr_timeunit++;
        prints("TM time unit count: ");
        printi(curr_timeunit);
    }
}