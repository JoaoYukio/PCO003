#include "kernel.h"
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

// Para compilar: gcc main.c kernel.c -o kernel

void wait( int seconds )
{   // Pretty crossplatform, both ALL POSIX compliant systems AND Windows
    #ifdef _WIN32
        Sleep( 1000 * seconds );
    #else
        sleep( seconds );
    #endif
}


char processo1()
{
    printf("Joao Yamashita\n");
    wait(2);
    return SUCCESS;
}

char processo2()
{
    printf("2017005768\n");
    wait(2);
    return SUCCESS;
}

char processo3()
{
    printf("UNIFEI\n");
    return REPEAT;
}

int count = 0;

char processo4()
{
    //count++;
    printf("PCO003 - %d\n", ++count);
    return REPEAT;
}


int main(void)
{
    kernelInit();
    process p1;
    p1.func = &processo1;
    p1.priority = 2;

    process p2;
    p2.func = &processo2;
    p2.priority = 3;

    process p3;
    p3.func = &processo3;
    p3.priority = 1;

    process p4;
    p4.func = &processo4;
    p4.priority = 1;

    kernelAddProc(&p1);
    kernelAddProc(&p2);
    kernelAddProc(&p3);
    kernelAddProc(&p4);

    kernelLoop();

    return 0;
}