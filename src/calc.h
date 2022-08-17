/*
----------------------MADE Milidors----------------------
------------------------2  0  2  2----------------------

*/
#ifndef _SRC_CALC_H
#define _SRC_CALC_H
#include "stack.h"

void mainFunction();
int getPrior(char opernand);
void workWithValue(char* expression, int size, queue** Node, stack** nodeStack);
char* inputExpression(int* size);
void menu(char oper, queue** headQueue, stack** headStack);
void addNumberInQueue(char exepression, queue** Node, char* number, char* minus, int iter, int size, int* createNodeQueue, int* size_of_array_numbers);
void parsNumber(char exepression, queue** Node, char* numbers, char* minus, int* size_of_array_numbers, char varForSearchMinus);
void parsOpernand(stack** nodeStack, queue** nodeQueue, char opernand, int prior, int countBracket, int* createNodeStack, int priorCheck);

void sum(queue** head);
void divi(queue** head);
void multi(queue** head);
void sub(queue** head);
void rebootArray(char* array, int size);
void lastCompute(stack** nodeStack, queue** nodeQueue);
void free_memory(char* array);
#endif // _SRC_CALC_H
