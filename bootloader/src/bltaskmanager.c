
#include "taskmanager.h"

void taskmain(){
    while(1){
        printf("Hello from taskmain!\n");
        WFI();
        printf("Found interrupt!\n");
    }
    return;
}