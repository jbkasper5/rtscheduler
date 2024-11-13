#include <stdio.h>
#include <string.h>

#ifndef __MACRO_H__
#define __MACRO_H__
#include "macros.h"
#endif

#ifndef __HEADER_H__
#define __HEADER_H__
#include "tasks.h"
#endif

#define ITEMS_PER_LINE  7
#define DELIMITER       ","

enum PARSE_CODES{
    ERROR,
    SUCCESS
};

char* read_line(FILE* file);
taskset_t* parse_taskset(char* path);