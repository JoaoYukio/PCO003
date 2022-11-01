#ifndef KERNEL_H
#define KERNEL_H

//return codes
#define SUCCESS   0
#define FAIL      1
#define REPEAT    2

//function pointer declaration
typedef char(*ptrFunc)(void);

//process struct
typedef struct {
	ptrFunc func;
    int priority;
} process;

//Kernel Functions

char kernelInit(void);
char kernelAddProc(process * newProc);
void kernelLoop(void);

#endif