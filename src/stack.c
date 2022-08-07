#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
void mainFunction()
{
    queue* nodeQueue;
    stack* nodeStack;
    char *expression;
    int size = 0;
    expression = inputExpression(&size);
    printf("VALUE: %s", expression);
    printf("\nSIZE: %d", size);
    parserNumber(expression, size, &nodeQueue);
    parserOpernand(expression, size, &nodeStack, &nodeQueue);
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

void parserNumber(char *expression, int size, queue** Node)
{
    int size_of_array_numbers = 0, createNode = 0;
    char *numbers = (char *)calloc(size, sizeof(char));
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
            if (createNode == 0) {
                *Node = initQueue(num);
                createNode = 1;
                size_of_array_numbers = 0;
            // Иначе добавляем последующие эл-ты
            } else {
            pushQueue(num, Node);  
            size_of_array_numbers = 0;
            }
        }
        // Перезапись массива
        if (size_of_array_numbers == 0) {
            for (int i = 0; i < size; i++) {
                numbers[i] = ' ';
            }
        }
    }
    free(numbers);
}


// Парсер опернандов набо будет переделать 
// Расписать все слуучаи выполнения определнных операций 
// позже раскидать все по отдельным функциям
// функцию занести в парсинг чисел

void parserOpernand(char *expression, int size, stack** Node, queue** nodeQueue) {
    char *opernand = (char *)calloc(size, sizeof(char));
    int size_of_array_opernand = 0, prior = 0, createNode = 0, priorCheck = -1;
    for (int i = 0; i < size; i++)
    {
        if (expression[i] >= '(' && expression[i] <= '/') {
            opernand[size_of_array_opernand] = expression[i];
            prior = getPrior(opernand[size_of_array_opernand]);
            if (priorCheck == -1) {
                if (createNode == 0) {
                    *Node = initStack(prior, opernand[size_of_array_opernand]);
                    size_of_array_opernand = 0;
                    createNode = 1;
                } else {
                    priorCheck =  printPrior(*Node);
                    if (prior == priorCheck) {
                        menu(opernand[size_of_array_opernand], nodeQueue);
                    } else if (prior > priorCheck) {
                        pushStack(prior, opernand[size_of_array_opernand], Node);
                    }
                    size_of_array_opernand = 0;
                }
            } else {
                 priorCheck =  printPrior(*Node);
                    if (prior == priorCheck) {
                        menu(opernand[size_of_array_opernand], nodeQueue);
                    } else if (prior > priorCheck) {
                        pushStack(prior, opernand[size_of_array_opernand], Node);
                    }
                    size_of_array_opernand = 0;
            }
        }
    }
    free_memory(opernand);
}
// Очистка памяти
void free_memory(char* array) {
    free(array);
}
// Инициализация стэка
stack *initStack(int prior, char opernand) {
    stack* tmp = (stack*)malloc(sizeof(stack));
    tmp -> prior = prior;
    tmp -> opernand = opernand;
    tmp ->next = NULL;
    return(tmp);
}
// Инициализация очереди
queue *initQueue(int num) {
    queue* tmp = (queue*)malloc(sizeof(queue));
    tmp -> number = num;
    tmp ->next = NULL;
    return(tmp);
}

// Добавление элементов в стек

void pushStack(int p, char oper, stack** head) {
    stack* tmp = (stack*)malloc(sizeof(stack));
    tmp->opernand = oper;
    tmp->prior = p; // Приоритет
    tmp->next = (*head);
    (*head) = tmp;
}

// Добавление элементов в очередь
void pushQueue(int num, queue** head) {
    queue* tmp = (queue*)malloc(sizeof(queue));
    tmp->number = num;
    tmp->next = (*head);
    (*head) = tmp;
}
int popQueue(queue** head){
    queue* tmp = NULL;
    int value = 0;
    if (head == NULL) {
        exit(-1);
    }
    tmp = (*head);
    value = tmp ->number;
    (*head) = (*head)->next;
    free(tmp);
    return value;
}
char popStack(stack** head){
    stack* tmp = NULL;
    char value;
    if (head == NULL) {
        exit(-1);
    }
    tmp = (*head);
    value = tmp ->opernand;
    (*head) = (*head)->next;
    free(tmp);
    return value;
}
// Нахождение приоритета знака
int getPrior(char opernand) {
    int prior = 0;
    if (opernand == '(') prior = 0;
    else if (opernand == '+') prior = 1;
    else if (opernand == '-') prior = 1;
    else if (opernand == '*') prior = 2;
    else if (opernand == '/') prior = 2;
    else if (opernand == '^') prior = 3;
    else if (opernand == '~') prior = 4;
    return prior;
}
// Вывод всех эл-тов в очереди
void printLinkedListQueue(queue *head) {
    printf("\nNUMBERS IN STACK\n");
    while (head != NULL) {
        printf("%d ", head->number);
        head = head->next;
    }
    printf("\n");
}
void printLinkedListStack(stack *head) {
    printf("\nOPERNAND IN STACK\n");
    while (head != NULL) {
        printf("%c: ", head->opernand);
        printf("%d ", head->prior);
        head = head->next;
        printf("\n");

    }
    printf("\n");
}
int printPrior(stack *head) {
        return head->prior;
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
    int sum = 0, a = 0, b = 0;
    a = popQueue(head);
    b = popQueue(head);
    sum = a + b;
    pushQueue(sum, head);
}
void divi(queue** head) {
    int sum = 0, a = 0, b = 0;
    a = popQueue(head);
    b = popQueue(head);
    sum = a / b;
    pushQueue(sum, head);
}
void multi(queue** head) {
    int sum = 0, a = 0, b = 0;
    a = popQueue(head);
    b = popQueue(head);
    sum = a * b;
    pushQueue(sum, head);
}
void sub(queue** head) {
    int sum = 0, a = 0, b = 0;
    a = popQueue(head);
    b = popQueue(head);
    sum = a - b;
    pushQueue(sum, head);
}
