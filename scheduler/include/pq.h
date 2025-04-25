#ifndef __PQ_H__
#define __PQ_H__

#include "macros.h"
#include "malloc.h"

typedef struct pqnode_s{
    int priority;
    int remaining;
    int deadline;
    int task;
}pqnode_t;

typedef struct pq_s{
    pqnode_t* arr;
    int size;                   // phsysical length
    int len;                   // logical length
}pq_t;

pq_t* pq_init(unsigned int items);
void pq_destroy(pq_t* pq);

void sink(pq_t* pq, int idx);
void swim(pq_t* pq, int idx);
void pq_add(pq_t* pq, int priority, int remaining, int deadline, int task);

pqnode_t* peek(pq_t* pq);
int pop(pq_t* pq);

#endif