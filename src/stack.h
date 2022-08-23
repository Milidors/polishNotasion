/*
----------------------MADE Milidors----------------------
------------------------2  0  2  2----------------------

*/

#ifndef _SRC_STACK_H
#define _SRC_STACK_H

// ______________________________________
typedef struct Stack
{
    int prior;
    char opernand;
    struct Stack *next;

} stack;
typedef struct Queue
{
    float number;
    struct Queue *next;
} queue;
// ______________________________________

// ___________INIT STACK___________________
stack *initStack(int prior, char opernand);
queue *initQueue(int number);
// ______________________________________

// ______________________________________
char popStack(stack **Node);
float popQueue(queue **Node);
// ______________________________________

// _____________FOR DEBUG________________
void printLinkedListQueue(queue *head);
void printLinkedListStack(stack *head);
//_______________________________________

int printPrior(stack *head);
int sizeQueue(queue *head);
int sizeStack(stack *head);

// ______________________________________
void pushStack(int prior, char opernand, stack **head);
void pushQueue(float num, queue **head);
// ______________________________________

void deleteFirstElementInStack(stack **head);

// ___________CLEAR MEMORY_______________
void deleteQueue(queue **head);
void deleteStack(stack **head);
// ______________________________________

#endif // _SRC_STACK_H
