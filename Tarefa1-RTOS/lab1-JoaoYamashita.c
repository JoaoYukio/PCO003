#include <stdio.h>

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
    head = 0;
    tail = 0;
}

int isEmpty(CQueue* q)
{
    return (q->head == q->tail)?1:0;
}

int isFull(CQueue* q)
{
    return (((q->tail+1)%q->size) == q->head)?1:0;
}
void main(void)
{
    
}