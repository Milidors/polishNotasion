#include "calc.h"
#include <stdlib.h>
#include <stdio.h>
void mainFunction()
{
    queue* nodeQueue;
    stack* nodeStack;
    char *expression;
    int size = 0;
    expression = inputExpression(&size);
    printf("VALUE: %s", expression);
    printf("\nSIZE: %d", size);
    parserNumber(expression, size, &nodeQueue, &nodeStack);
    printf("\n");
    printLinkedListQueue(nodeQueue);
    printLinkedListStack(nodeStack);
    free_memory(expression);
}
// Ввод значений
char *inputExpression(int *size)
{
    char *expression = (char*)calloc(*size+1, sizeof(char));
    char sym = getchar();
    while (sym != '\0' && sym != '\n')
    {
        expression[*size] = sym;
        *size += 1;
        expression = (char*)realloc(expression, *size+1);
        sym = getchar();
    }
    return expression;
}

void parserNumber(char *expression, int size, queue** Node, stack** nodeStack)
{
    int size_of_array_numbers = 0, createNodeQueue = 0, size_of_array_opernand = 0, prior;
    int createNodeStack = 0, priorCheck = -1, sizeNode = 0;
    char *numbers = (char *)calloc(size, sizeof(char));
    char *opernand = (char *)calloc(size, sizeof(char));
    for (int i = 0; i < size; i++)
    {
        // парсинг чисел
        if (expression[i] >= '0' && expression[i] <= '9') {
            numbers[size_of_array_numbers] = expression[i]; 
            size_of_array_numbers += 1;
            
        }
        // Добавление каждого числа в стэк
        if (((expression[i] >= '(' && expression[i] <= '/') || (i + 1 == size)) &&( 
        expression[i] != '\n' && expression[i] != '\0' && numbers[0] != ' ')) {
            int num = atoi(numbers); 
            // Если стек пустой то добавляем первый элемент
            if (createNodeQueue == 0) {
                *Node = initQueue(num);
                createNodeQueue = 1;
                size_of_array_numbers = 0;
            // Иначе добавляем последующие эл-ты
            } else {
            pushQueue(num, Node);  
            size_of_array_numbers = 0;
            }
        }
        if (i + 1 == size) {
            menu(popStack(nodeStack), Node);
            sizeNode = sizeQueue(*Node);
        }
        if (expression[i] >= '(' && expression[i] <= '/') {
            opernand[size_of_array_opernand] = expression[i];
            prior = getPrior(opernand[size_of_array_opernand]);
            if (priorCheck == -1) {
                if (createNodeStack == 0) {
                    *nodeStack = initStack(prior, opernand[size_of_array_opernand]);
                    createNodeStack = 1;
                    priorCheck = 1;
                } 
            } else {
                 priorCheck = printPrior(*nodeStack);
                    if (prior == priorCheck) {
                        menu(popStack(nodeStack), Node);
                        pushStack(prior, opernand[size_of_array_opernand], nodeStack);
                    } else if (prior > priorCheck) {
                        pushStack(prior, opernand[size_of_array_opernand], nodeStack);
                    } else if (prior < priorCheck && prior != 0) {
                        menu(popStack(nodeStack), Node);
                        pushStack(prior, opernand[size_of_array_opernand], nodeStack);
                    } else if (prior == 0) {
                        pushStack(prior, opernand[size_of_array_opernand], nodeStack);
                    } else if (prior == 0 && priorCheck == 0) {
                        printf("ENTER");
                        deleteFirstElementInStack(nodeStack);
                        deleteFirstElementInStack(nodeStack); 
                    }
            }           
        }
        // Перезапись массива
        if (size_of_array_numbers == 0) {
            for (int i = 0; i < size; i++) {
                numbers[i] = ' ';
            }
        }
    }
    if (sizeNode > 1) {
        while (sizeNode > 1)
        {
            printLinkedListStack(*nodeStack);
            // printf("%d", sizeNode);
            menu(popStack(nodeStack), Node);
            sizeNode -= 1;
        }
    }
    free(numbers);
}

void menu(char oper, queue** headQueue) {
    switch (oper)
    {
        case '+':
            sum(headQueue);
            break;
        case '-':
            sub(headQueue);
            break;
        case '*':
            multi(headQueue);
            break;
        case '/':
            divi(headQueue);
            break;
        default:
            break;
    }
}
void sum(queue** head) {
    float sum = 0, a = 0, b = 0;
    a = popQueue(head);
    b = popQueue(head);
    sum = a + b;
    pushQueue(sum, head);
}
void divi(queue** head) {
    float sum = 0, a = 0, b = 0;
    a = popQueue(head);
    b = popQueue(head);
    sum = b / a;
    pushQueue(sum, head);
}
void multi(queue** head) {
    float sum = 0, a = 0, b = 0;
    a = popQueue(head);
    b = popQueue(head);
    sum = a * b;
    pushQueue(sum, head);
}
void sub(queue** head) {
    float sum = 0, a = 0, b = 0;
    a = popQueue(head);
    b = popQueue(head);
    sum = b - a;
    pushQueue(sum, head);
}
int getPrior(char opernand) {
    int prior = 0;
    if (opernand == '(' || opernand == ')') prior = 0;
    else if (opernand == '+') prior = 1;
    else if (opernand == '-') prior = 1;
    else if (opernand == '*') prior = 2;
    else if (opernand == '/') prior = 2;
    else if (opernand == '^') prior = 3;
    else if (opernand == '~') prior = 4;
    return prior;
}
void free_memory(char* array) {
    free(array);
}
