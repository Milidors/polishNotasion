#ifndef _SRC_STACK_H
#define _SRC_STACK_H

typedef struct Stack
{
    int prior;
    char opernand;
    struct Stack* next;
    
} stack;
typedef struct Queue
{
    float number;
    struct Queue* next;
} queue;
stack *initStack(int prior, char opernand);
queue *initQueue(int number);
char popStack(stack **Node);
float popQueue(queue **Node);
void printLinkedListQueue(queue *head);
void printLinkedListStack(stack *head);
int printPrior(stack *head);
int sizeQueue(queue* head);
void pushStack(int prior, char opernand, stack** head);
void pushQueue(float num, queue** head);
void deleteFirstElementInStack(stack** head);
void deleteQueue(queue** head);
void deleteStack(stack** head);
#endif // _SRC_STACK_H
