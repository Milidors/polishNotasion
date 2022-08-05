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
stack *init_stack(int prior, char opernand);
queue *init_queue(int number);
char pop_stack(stack **Node);
char pop_queue(queue **Node);
void check_on_null_queue(queue **Node);
void printLinkedListQueue(queue *head);
void printLinkedListStack(stack *head);
void push_stack(int prior, char opernand, stack** head);
void push_queue(int num, queue** head);

void main_function();
int get_prior(char opernand);
void parser_number(char* expression, int size, queue** Node);
char* input_expression(int* size);
void parser_opernand(char *expression, int size, stack** Node);
void free_memory(char* array);
#endif // _SRC_STACK_H