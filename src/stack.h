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
    int number;
    struct Queue* next;
} queue;
stack *initStack(int prior, char opernand);
queue *initQueue(int number);
char popStack(stack **Node);
int popQueue(queue **Node);
// void check_on_null_queue(queue **Node);
void printLinkedListQueue(queue *head);
void printLinkedListStack(stack *head);
int printPrior(stack *head);
void pushStack(int prior, char opernand, stack** head);
void pushQueue(int num, queue** head);

void mainFunction();
int getPrior(char opernand);
void parserNumber(char* expression, int size, queue** Node, stack** nodeStack);
char* inputExpression(int* size);
void parserOpernand(char *expression, int size, stack** Node, queue** nodeQueue);
void menu(char oper, queue** headQueue); 
void workWithMenu(stack** headStack, queue** headQueue);
// Сложение
void sum(queue** head);
//  Деление
void divi(queue** head);
// Умножение
void multi(queue** head);
// Вычитание
void sub(queue** head);
void free_memory(char* array);
#endif // _SRC_STACK_H 