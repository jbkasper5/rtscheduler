#include <stdio.h>
#include <string.h>

#ifndef __HEADER_H__ // If this is NOT defined
#define __HEADER_H__ // Define it for the first time

#include "tasks.h"

#endif // Toes protected

#define ITEMS_PER_LINE  7
#define DELIMITER       ":"

enum PARSE_CODES{
    ERROR,
    SUCCESS
};

char* read_line(FILE* file);
taskset_t* parse_taskset(char* path);