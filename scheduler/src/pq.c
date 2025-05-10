#include "pq.h"

#define NOP -1
#define PARENT(x)       ((x - 1) / 2)
#define LEFTCHILD(x)    ((2 * x) + 1)
#define RIGHTCHILD(x)   ((2 * x) + 2)

void swap(pq_t* pq, int idx1, int idx2);

pq_t* pq_init(unsigned int items){
    pq_t* pq = (pq_t*)malloc(sizeof(pq_t));
    if(!pq) return NULL;
    pq->arr = (pqnode_t*)malloc(sizeof(pqnode_t) * items);
    if(!pq->arr){
        free (pq);
        return NULL;
    }
    pq->size = items;
    pq->len = 0;
    return pq;
}

void pq_destroy(pq_t* pq){
    if(!pq) return;
    free(pq->arr);
    free(pq);
}

void pq_add(pq_t* pq, int priority, int remaining, int deadline, int task){
    if(!pq) return;
    pq->arr[pq->len].priority = priority;
    pq->arr[pq->len].task = task;
    pq->arr[pq->len].remaining = remaining;
    pq->arr[pq->len].deadline = deadline;
    swim(pq, pq->len++);
}

void swap(pq_t* pq, int idx1, int idx2){
    pqnode_t temp = pq->arr[idx1];
    pq->arr[idx1] = pq->arr[idx2];
    pq->arr[idx2] = temp;
}

void sink(pq_t* pq, int idx){
    int lc = LEFTCHILD(idx);
    int rc = RIGHTCHILD(idx);

    if(lc <= pq->len && rc <= pq->len){
        // both children exist, figure out which to swap with 
        if(pq->arr[idx].priority < pq->arr[lc].priority || pq->arr[idx].priority < pq->arr[rc].priority){
            
            // determine whether the left or right child has higher priority
            int minIdx = (MIN(pq->arr[lc].priority, pq->arr[rc].priority) == pq->arr[lc].priority) ? lc : rc;
            
            // swap and continue to sink
            swap(pq, idx, minIdx);
            sink(pq, minIdx);
        }
    }else if(lc <= pq->len){
        if(pq->arr[idx].priority < pq->arr[lc].priority){

            // if left child has higher priority than the parent, swap and continue to sink
            swap(pq, idx, lc);
            sink(pq, lc);
        }
    }
}

void swim(pq_t* pq, int idx){
    if(idx <= 0) return;
    if(pq->arr[PARENT(idx)].priority > pq->arr[idx].priority){
        swap(pq, PARENT(idx), idx);
        swim(pq, PARENT(idx));
    }
}

pqnode_t* peek(pq_t* pq){
    if(!pq->len) return NULL;
    return pq->arr;
}

int pop(pq_t* pq){
    if(!pq->len) return NOP;
    pqnode_t head = pq->arr[0];
    pq->arr[0] = pq->arr[pq->len - 1];
    pq->len--;
    sink(pq, 0);
    return head.task;
}