#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void (*pontFunc)(void); //ponteiro que retorna void e recebe void

typedef struct {
    char* nome;
    int time;
    pontFunc myFunction;
}process;

typedef struct {
    int head;
    int tail;
    int size;
    process* arr;
}CQueue;

void createCQueue(CQueue* q, int size)
{
    q->arr = (process*)malloc(sizeof(process)*size);
    q->size = size;
    q->head = 0;
    q->tail = 0;
}

int isEmpty(CQueue* q)
{
    return (q->head == q->tail)?1:0;
}

int isFull(CQueue* q)
{
    return (((q->tail+1)%q->size) == q->head)?1:0;
}

int enqueue(CQueue* q, process p)
{
    if(!isFull(q))
    {
        q->arr[q->tail] = p;
        q->tail = (q->tail+1)%q->size;
        return 1;
    }
    return 0;
}

void dequeue(CQueue* q)
{
    if(!isEmpty(q))
    {
        q->head = (q->head+1)%q->size;
    }   
}

void displayQueue(CQueue* q)
{
    int start = q->head;
    while(start!=q->tail)
    {
        printf("%s ",q->arr[start].nome);
        start = (start+1)%q->size;
    }
}

void addProc(CQueue* q, char* nome, int time, pontFunc f)
{
    process p;
    p.nome = nome;
    p.time = time; 
    p.myFunction = f;
    enqueue(q, p);
}

void execProc(CQueue* q)
{
    if(isEmpty(q))return;
    //Executa o primeiro processo na fila, ou seja, o processo na head
    (*q->arr[q->head].myFunction)();
    //Espera pelo tempo determinado pela struct
    _sleep(1000*q->arr[q->head].time);//Tempo em ms
}

void RemoveProc(CQueue* q)
{
    // Manter compatibilidade com o modelo do exercicio
    dequeue(q);
}

void fun1(void)
{
    printf("Ola mundo, sou a funcao 1\n");
}

void fun2(void)
{
    printf("Ola mundo, sou a funcao 2\n");
}

void fun3(void)
{
    printf("Ola mundo, sou a funcao 3\n");
}

void main(void)
{
    CQueue FilaCircular;

    createCQueue(&FilaCircular, 5);

    addProc(&FilaCircular, "Processo1", 1, &fun1);
    addProc(&FilaCircular, "Processo2", 2, &fun2);
    addProc(&FilaCircular, "Processo3", 3, &fun3);

    execProc(&FilaCircular);
    RemoveProc(&FilaCircular);
    execProc(&FilaCircular);
    RemoveProc(&FilaCircular);
    execProc(&FilaCircular);
    RemoveProc(&FilaCircular);

    if(isEmpty(&FilaCircular))
    {
        printf("Fila Vazia\n");
    }else{
        printf("Fila ainda tem processos");
    }
}