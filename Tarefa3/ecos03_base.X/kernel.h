/* 
 * File:   kernel.h
 * Author: Rodrigo
 *
 * Created on 25 de Março de 2015, 07:20
 */

#ifndef KERNEL_H
#define	KERNEL_H

//return code
#define SUCCESS  0
#define FAIL     1
#define REPEAT   2

#define POOLSIZE 10
//function pointer declaration
typedef char (*ptrFunc)(void);

//process struct

typedef struct {
    ptrFunc function;
    int period;
    int start;
    int prio;
} process;



char kernelInit(void);
char kernelAddProc(process* newProc);
void kernelLoop(void);

void KernelClock(void);


#endif	/* KERNEL_H */

