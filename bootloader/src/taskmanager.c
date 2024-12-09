
#include "taskmanager.h"

void taskmain(){
    lock_acquire();
    prints("Hello from taskmain!\n");
    lock_release();
    return;
}