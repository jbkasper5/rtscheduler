#include "taskmanager.h"
#include "print.h"
#include "time.h"
#include "malloc.h";

void task(unsigned long execution_time);

void tm_main(void){
    prints("In TM\n");
    while(1){
        prints("TM going to sleep...\n");
        wait_for_interrupt();
        prints("TM woke up\n");
    }
    return;
}


// function to spin a task for it's execution time
void task(unsigned long execution_time){
    wait_for_interrupt();
}