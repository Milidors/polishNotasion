#include "calc.h"
#include <stdlib.h>
#include <stdio.h>
/*
----------------------MADE Milidors----------------------
------------------------2  0  2  2----------------------
*/

void mainFunction() 
{       queue* nodeQueue;
        stack* nodeStack;
        char *expression;
    while (1)
    {
        int size = 0;
        expression = inputExpression(&size);
        workWithValue(expression, size, &nodeQueue, &nodeStack);
        printf("\n");
        printf("VALUE: %s = ", expression);
        printLinkedListQueue(nodeQueue);
        printf("----------------------------\n");
    }
    free_memory(expression);
    deleteQueue(&nodeQueue);
    deleteStack(&nodeStack);
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
void workWithValue(char *expression, int size, queue** nodeQueue, stack** nodeStack)
{
    int size_of_array_numbers = 0, createNodeQueue = 0, prior = 0;
    int createNodeStack = 0, priorCheck = -1, sizeNode = 0, countBracket = 0;
    char *numbers = (char *)calloc(size, sizeof(char));
    char minus;
    for (int i = 0; i < size; i++)
    {
        // ____________________WORK WITH QUEUE____________________________
        parsNumber(expression[i], nodeQueue, numbers, &minus, &size_of_array_numbers, expression[i-1]);
        addNumberInQueue(expression[i], nodeQueue, numbers, &minus, i, size, &createNodeQueue, &size_of_array_numbers);
        // _______________________WORK WITH LAST ELEMENT IN STACK_______________________________
        if (i + 1 == size) {
            menu(popStack(nodeStack), nodeQueue, nodeStack);
            sizeNode = sizeQueue(*nodeQueue);
        }

        // ____________________________WORK WITH STACK________________________________
        if (expression[i] >= '(' && expression[i] <= '/') {
            parsOpernand(nodeStack, nodeQueue, expression[i], prior, countBracket, &createNodeStack, priorCheck);
            }
        // __________________________REBOOT ARRAY____________________
        if (size_of_array_numbers == 0) {
            rebootArray(numbers,  size);
        }
    }
    
    if (sizeNode > 1) {
        lastCompute(nodeStack, nodeQueue);
    }
    free_memory(numbers);    
}
void parsOpernand(stack** nodeStack, queue** nodeQueue,char opernand, int prior, int countBracket, int* createNodeStack, int priorCheck) {
            prior = getPrior(opernand);
            if (*createNodeStack == 0) {
                *nodeStack = initStack(prior, opernand);
                *createNodeStack = 1;
            } 
             else {
                 priorCheck = printPrior(*nodeStack);
                    if (prior == priorCheck && ((prior != 0 && priorCheck != 0) && (prior != -1 && priorCheck != -1))) {
                        
                        menu(popStack(nodeStack), nodeQueue, nodeStack);
                        pushStack(prior, opernand, nodeStack);
                    } else if ((prior > priorCheck)) {
                        pushStack(prior, opernand, nodeStack);
                    } else if (prior < priorCheck && (prior != 0 && prior != -1)) {

                        menu(popStack(nodeStack), nodeQueue, nodeStack);
                        pushStack(prior, opernand, nodeStack);
                    } else if (prior == 0) {
                        pushStack(prior, opernand, nodeStack);
                        countBracket += 1;
                    } 
                    else if (prior == -1) {

                        if (countBracket >= 0) {
                            while (priorCheck != 0)
                            {
                                menu(popStack(nodeStack), nodeQueue, nodeStack);
                                priorCheck = printPrior(*nodeStack); 
                            }
                            deleteFirstElementInStack(nodeStack);
                            countBracket -= 1;
                        }   
                    }
                }           
}
void parsNumber(char expression, queue** Node, char* numbers, char* minus, int* size_of_array_numbers, char searchMinus) {
    
    if ( (expression >= '0' && expression <= '9')) {
            numbers[*size_of_array_numbers] = expression; 
            *size_of_array_numbers += 1;
            if (searchMinus == '-') {
                *minus = '-';
            }       
}
}
void addNumberInQueue(char expression, queue** Node, char* numbers, char* minus, int iter, int size, int* createNodeQueue, int* size_of_array_numbers) {
    if (((expression >= '(' && expression <= '/') || (iter + 1 == size)) &&( 
        expression != '\n' && expression != '\0' && numbers[0] != ' ')) {
            int num;
            if(*minus == '-') {
                num = -atoi(numbers);
                *minus = ' ';
            } 
             else {
                num = atoi(numbers);
            }
            // Если очередь пустоая то добавляем первый элемент
            if (*createNodeQueue == 0) {
                *Node = initQueue(num);
                *createNodeQueue = 1;
                *size_of_array_numbers = 0;
            // Иначе добавляем последующие эл-ты
            } else {
            pushQueue(num, Node);  
            *size_of_array_numbers = 0;
            }
        }
}

// _________________________MENU_________________________
void menu(char oper, queue** headQueue, stack** headStack) {
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
        default: break;
    }
}
void rebootArray(char* array, int size) {
    for (int i = 0; i < size; i++) {
                array[i] = ' ';
            }
}
void lastCompute(stack** nodeStack, queue** nodeQueue) {
    int sizeS = sizeStack(*nodeStack);
    while (sizeS > 0) {
                menu(popStack(nodeStack), nodeQueue, nodeStack);
                sizeS = sizeStack(*nodeStack);
    }
}
void sum(queue** head) {
    float sum = 0.0, a = 0.0, b = 0.0;
    a = popQueue(head);
    b = popQueue(head);
    sum = a + b;
    pushQueue(sum, head);
}
void divi(queue** head) {
    float sum = 0.0, a = 0.0, b = 0.0;
    a = popQueue(head);
    b = popQueue(head);
    sum = b / a;
    pushQueue(sum, head);
}
void multi(queue** head) {
    float sum = 0.0, a = 0.0, b = 0.0;
    a = popQueue(head);
    b = popQueue(head);
    sum = b * a;
    pushQueue(sum, head);
}

void sub(queue** head) {
    float sum = 0.0, a = 0.0, b = 0.0;
    a = popQueue(head);
    b = popQueue(head);
    sum = b - a;
    if (a > 0) {
        sum = b - a;
    } else 
        sum = b + a;
    pushQueue(sum, head);
}
int getPrior(char opernand) {
    int prior = 0;
    if (opernand == '(') prior = 0;
    else if (opernand == ')') prior = -1;
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
