
#include "taskmanager.h"

void taskmain(){
    while(1){
        prints("Hello from taskmain!\n");
        WFI();
        prints("Found interrupt!\n");
    }
    return;
}