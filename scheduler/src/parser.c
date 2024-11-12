#include "parser.h"

char* read_line(FILE* file){
    int chars_per_line = 0;
    char c;

    // scan the line character by character until we reach a newline token
    while((c = fgetc(file)) != '\n'){
        // if configuration file is written correctly, we should never read an EOF token
        if(c == EOF){
            printf("Error: unexpected EOF reached when parsing file.\n");
            exit(1);
        }
        chars_per_line++;
    }
    // allocate memory for line, 1 for null terminator
    char* str = malloc((sizeof(char) * chars_per_line) + 1);
    if(!str){
        printf("Error: could not allocate space to store line.\n");
        exit(1);
    }

    // back up the number of characters we read + 1 (for the newline token) 
    fseek(file, -chars_per_line - 1, SEEK_CUR);

    // read line into buffer
    fread(str, sizeof(char), chars_per_line, file);

    // skip past newline character
    fseek(file, 1, SEEK_CUR);

    // set delimiter
    str[chars_per_line] = '\0';
    return str;
}

void parse_task(taskset_t* taskset, int task, char** line){
    // line[1];                                    // task type
    taskset->tasks[task].execution_time = strtof(line[2], NULL);     // execution time
    taskset->tasks[task].period = strtof(line[3], NULL);             // period
    taskset->tasks[task].refresh = strtof(line[4], NULL);            // refresh
    taskset->tasks[task].deadline = strtof(line[5], NULL);           // deadline
    taskset->tasks[task].offset = strtof(line[6], NULL);             // offset
}

taskset_t* parse_taskset(char* path){
    FILE* file = fopen(path, "r");
    if(!file){
        printf("Error: file '%s' not found.\n", path);
        exit(1);
    }

    // first line of file should be a single integer
    char* line = read_line(file);

    if(strlen(line) != 1){
        printf("Error: configuration file format not recognized.\n");
        exit(1);
    }

    // convert that to an actual integer, ensuring validity
    int num_tasks = atoi(line);
    if(num_tasks == 0){
        printf("Error: Specify valid number of tasks (integer > 0).\n");
        exit(1);
    }

    // free the first line, now we'll be parsing the task definition lines
    free(line);

    // create the taskset
    taskset_t* taskset = taskset_init(num_tasks);

    char* linesep[ITEMS_PER_LINE];

    for(int i = 0; i < num_tasks; i++){

        // read the current task declaration line
        line = read_line(file);

        // separate into the repsective task attributes with strtok
        linesep[0] = strtok(line, DELIMITER);
        for(int j = 1; j < ITEMS_PER_LINE; j++){
            linesep[j] = strtok(NULL, DELIMITER);

            // sanity check to make sure parsing is successful
            if(!linesep[j]){
                printf("Error: error in separating input using delimiter '%s'.\n", DELIMITER);
                exit(1);
            }
        }

        // populate the task array with the current line we wish to parse
        parse_task(taskset, i, linesep);

        // free line allocated by read_line
        free(line);
    }
    return taskset;
}