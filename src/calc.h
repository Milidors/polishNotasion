#ifndef _SRC_CALC_H
#define _SRC_CALC_H
#include "stack.h"

void mainFunction();
int getPrior(char opernand);
void parserNumber(char* expression, int size, queue** Node, stack** nodeStack);
char* inputExpression(int* size);
void parserOpernand(char *expression, int size, stack** Node, queue** nodeQueue);
void menu(char oper, queue** headQueue, stack** headStack); 
void sum(queue** head);
void divi(queue** head);
void multi(queue** head);
void sub(queue** head);
void free_memory(char* array);
#endif // _SRC_CALC_H
