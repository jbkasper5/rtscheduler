#include "taskmanager.h"

void task(unsigned long execution_time);

// since the stacks are small ish, put this in static data since it's 1 KiB
ihc_msg_t msg;

void tm_main(void){
    long* val;
    unsigned int hart;
    while(1){
        // slep
        WFI();
        printf("TM: Reading message...\n");

        // once the tm is woked, read a communication from the scheduler
        read_message(hartid(), &msg);

        // do stuff with the scheduler's message

        // clear the message
        memset(&msg, 0, sizeof(ihc_msg_t));
    }
    return;
}


// function to spin a task for it's execution time
void task(unsigned long execution_time){
    WFI();
}