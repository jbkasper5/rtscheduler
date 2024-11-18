#include "taskmanager.h"

typedef struct TCB_s{

} tcb_t;

void signal_tm_ready(int signum);
void scheduler(void);