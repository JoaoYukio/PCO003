#include "kernel.h"
#include <pic18f4520.h>

process* pool[POOLSIZE];
char start, end;

char kernelInit(void) {
    start = 0;
    end = 0;
    return SUCCESS;
}

char kernelAddProc(process* newProc) {
    //checking for free space
    if (((end + 1) % POOLSIZE) != start) {
        pool[end] = newProc;
        pool[end]->start += newProc->period;
        end = (end + 1) % POOLSIZE;
        return SUCCESS;
    }
    return FAIL;
}

void kernelLoop(void) {
    char next, p;
    process * tempProc;
    for (;;) {
        //Do we have any process to execute?
        if (start != end) {
            //Find the process with the lowest timer
            next = start;
            for (p = start; p != end; p = (p + 1) % POOLSIZE) {
                if (pool[p]->start < pool[next]->start) {
                    next = p;
                }
            }
            //Exchanging processes positions
            tempProc = pool[next];
            pool[next] = pool[start];
            pool[start] = tempProc;

            //waiting for the process to be ready
            while (pool[start]->start > 0) {
                //Great place for energy saving
            }
            if (pool[start]->function() == REPEAT) {
                kernelAddProc(pool[start]);
            }
            start = (start + 1) % POOLSIZE;
        }

    }
}

#define MIN_INT -30000

void KernelClock(void) {
    unsigned char proc;
    for (proc = start; proc != end; proc = (proc + 1) % POOLSIZE) {
        if ((pool[proc]->start)>(MIN_INT)) {
            pool[proc]->start--;
        }
    }
}
