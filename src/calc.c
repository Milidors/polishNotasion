#include "calc.h"
#include <stdlib.h>
#include <stdio.h>
// проверка 5+4-20*99-140+259/4-10*93+5+1000/500
void mainFunction() 
{       queue* nodeQueue;
        stack* nodeStack;
        char *expression;
    while (1)
    {
        int size = 0;
        expression = inputExpression(&size);
        printf("VALUE: %s", expression);
        printf("\nSIZE: %d", size);
        parserNumber(expression, size, &nodeQueue, &nodeStack);
        printf("\n");
        printLinkedListQueue(nodeQueue);
        printLinkedListStack(nodeStack);
    }
    
        
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
    char minus;
    for (int i = 0; i < size; i++)
    {
        // ____________________WORK WITH QUEUE____________________________
        // парсинг чисел
        if ( (expression[i] >= '0' && expression[i] <= '9')) {
            numbers[size_of_array_numbers] = expression[i]; 
            size_of_array_numbers += 1;
            if (expression[i-1] == '-' ) {
                minus = '-';
            } 
            
        }
        // Добавление каждого числа в стэк
        if (((expression[i] >= '(' && expression[i] <= '/') || (i + 1 == size)) &&( 
        expression[i] != '\n' && expression[i] != '\0' && numbers[0] != ' ')) {
            int num;
            if(minus == '-') {
                num = -atoi(numbers);
                minus = ' ';
            } else {
                num = atoi(numbers);
            }
            // Если очередь пустоая то добавляем первый элемент
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

        // _______________________WORK WITH LAST ELEMENT IN STACK_______________________________
        if (i + 1 == size) {
            menu(popStack(nodeStack), Node, nodeStack);
            sizeNode = sizeQueue(*Node);
        }

        // ____________________________WORK WITH STACK________________________________
        if (expression[i] >= '(' && expression[i] <= '/') {
            opernand[size_of_array_opernand] = expression[i];
            prior = getPrior(opernand[size_of_array_opernand]);
            if (createNodeStack == 0) {
                *nodeStack = initStack(prior, opernand[size_of_array_opernand]);
                createNodeStack = 1;
            } 
             else {
                 priorCheck = printPrior(*nodeStack);
                 printf("\nENTER");
                    if (prior == priorCheck && ((prior != 0 && priorCheck != 0) && (prior != -1 && priorCheck != -1))) {
                        
                        menu(popStack(nodeStack), Node, nodeStack);
                        pushStack(prior, opernand[size_of_array_opernand], nodeStack);
                    } else if ((prior > priorCheck)) {
                        pushStack(prior, opernand[size_of_array_opernand], nodeStack);
                    } else if (prior < priorCheck && (prior != 0 && prior != -1)) {

                        menu(popStack(nodeStack), Node, nodeStack);
                        pushStack(prior, opernand[size_of_array_opernand], nodeStack);
                    } else if (prior == 0) {
                        pushStack(prior, opernand[size_of_array_opernand], nodeStack);
                    } 
                    else if (prior == -1) {
                        menu(popStack(nodeStack), Node, nodeStack);
                    }
            printLinkedListQueue(*Node);
                
            }           
        }
        // __________________________REBOOT ARRAY____________________
        // Перезапись массива
        if (size_of_array_numbers == 0) {
            for (int i = 0; i < size; i++) {
                numbers[i] = ' ';
            }
        }
    }
    // Переделать 
    // Считает только простые выражение на подобии 5*(2+10-45+54)
    // Не считает 5*(2+10-45+54)-45 или 5*(2+10-45+54*25/45-500) или 5*(2+10-45+54*25/45-500)-250 или 
    // 1000+5*(2+10-45+54*25/45-500+(250-450)*(50*2))-250+42123
    if (sizeNode > 1) {
        printLinkedListStack(*nodeStack);
        printLinkedListQueue(*Node);
        int sizeS = sizeStack(*nodeStack);
                printf("SIZE  = = = =%d", sizeS);

        while (sizeS > 0)
            {
                menu(popStack(nodeStack), Node, nodeStack);
                printLinkedListStack(*nodeStack);
                sizeS = sizeStack(*nodeStack);;
                printf("%d", sizeS);

            }
    }
    free_memory(numbers);
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
