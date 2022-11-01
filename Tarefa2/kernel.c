#include "kernel.h"
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
                int count = 0;
                int maxPrio = pool[start]->priority;
                process* maxPrioProcess = pool[start];
                while(pont != end)
                {
                    if(pool[pont]->priority > maxPrio)
                    {
                        maxPrio = pool[pont]->priority;
                        maxPrioProcess = pool[pont];
                    }
                    count++;
                }
                //swap
                process* temp = pool[start];
                pool[start] = maxPrioProcess;
                pool[count] = temp;

                //check if there is need to reschedule
                if (pool[start]->func() == REPEAT){
                    kernelAddProc(pool[start]);
                }
                //prepare to get the next process; 
                start = (start+1)%POOL_SIZE;
            }
}
}