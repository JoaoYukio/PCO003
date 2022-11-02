#include "kernel.h"

// TODO: Tentar usar uma lista de adjacencias para reduzir o custo para achar processo para O(1)
#define POOL_SIZE 10
process * pool[POOL_SIZE];
int start, end;
char kernelInit(void){
	start = 0;
	end = 0;
	return SUCCESS;
}
char kernelAddProc(process * newProc){
	//checking for free space
	if ( ((end+1)%POOL_SIZE) != start){
		pool[end] = newProc;
		end = (end+1)%POOL_SIZE;
		return SUCCESS;
	}
	return FAIL;
}

void kernelLoop(void){
    for(;;){
        //Do we have any process to execute?
        if (start != end){
            //check if there's a process with higher priority
            int pont = start;
            int maxPrio = pool[start]->priority;
            int maxPrioCount = start;
            while(pont != end)
            {
                if(pool[pont]->priority > maxPrio)
                {
                    maxPrio = pool[pont]->priority;
                    maxPrioCount = pont;
                }
                pont = (pont+1)%POOL_SIZE;;
            }
            //swap 
            process* temp = pool[start];
            pool[start] = pool[maxPrioCount];
            pool[maxPrioCount] = temp;

            //check if there is need to reschedule
            if (pool[start]->func() == REPEAT){
                kernelAddProc(pool[start]);
            }
            //prepare to get the next process; 
            start = (start+1)%POOL_SIZE;
        }
    }
}