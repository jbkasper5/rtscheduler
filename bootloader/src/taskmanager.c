
#include "taskmanager.h"

void taskmain(){
    while(1){
        prints("Hello from taskmain!\n");
        wait_for_interrupt();
        prints("Found interrupt!\n");
    }
    return;
}