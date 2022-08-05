#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
void main_function()
{
    queue* nodeQueue;
    stack* nodeStack;
    char *expression;
    int size = 0;
    expression = input_expression(&size);
    printf("VALUE: %s", expression);
    printf("\nSIZE: %d", size);
    parser_number(expression, size, &nodeQueue);
    parser_opernand(expression, size, &nodeStack);
    printf("\n");
    printLinkedListQueue(nodeQueue);
    printLinkedListStack(nodeStack);
    free_memory(expression);
}
// Ввод значений
char *input_expression(int *size)
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

void parser_number(char *expression, int size, queue** Node)
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
        if ((expression[i] >= '(' && expression[i] <= '/') || i + 1 == size) {
            int num = atoi(numbers); 
            printf("\n1___%d___", num);
            // Если стек пустой то добавляем первый элемент
            if (createNode == 0) {
                printf("\n____ENTER___");
                *Node = init_queue(num);
                createNode = 1;
                size_of_array_numbers = 0;
            // Иначе добавляем последующие эл-ты
            } else {
            push_queue(num, Node);  
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
void parser_opernand(char *expression, int size, stack** Node) {
    char *opernand = (char *)calloc(size, sizeof(char));
    int size_of_array_opernand = 0, prior = 0, createNode = 0;
    for (int i = 0; i < size; i++)
    {
        if (expression[i] >= '(' && expression[i] <= '/') {
            opernand[size_of_array_opernand] = expression[i];
            prior = get_prior(opernand[size_of_array_opernand]);
            if (createNode == 0) {
                *Node = init_stack(prior, opernand[size_of_array_opernand]);
                size_of_array_opernand = 0;
                createNode = 1;
            } else {
                push_stack(prior, opernand[size_of_array_opernand], Node);
                size_of_array_opernand = 0;
            }
            printf("\nPRIOR %d %c", prior, opernand[size_of_array_opernand]);
        }
    }
    free_memory(opernand);
}
// Очистка памяти
void free_memory(char* array) {
    free(array);
}
// Инициализация стэка
stack *init_stack(int prior, char opernand) {
    stack* tmp = (stack*)malloc(sizeof(stack));
    tmp -> prior = prior;
    tmp -> opernand = opernand;
    tmp ->next = NULL;
    return(tmp);
}
// Инициализация очереди
queue *init_queue(int num) {
    queue* tmp = (queue*)malloc(sizeof(queue));
    tmp -> number = num;
    tmp ->next = NULL;
    return(tmp);
}

// Добавление элементов в стек

void push_stack(int p, char oper, stack** head) {
    stack* tmp = (stack*)malloc(sizeof(stack));
    tmp->opernand = oper;
    tmp->prior = p; // Приоритет
    tmp->next = (*head);
    (*head) = tmp;
}

// Добавление элементов в очередь
void push_queue(int num, queue** head) {
    queue* tmp = (queue*)malloc(sizeof(queue));
    tmp->number = num;
    tmp->next = (*head);
    (*head) = tmp;
}

// Нахождение приоритета знака
int get_prior(char opernand) {
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
    printf("\nNUMBERS IN STACK\n");
    while (head != NULL) {
        printf("%c: ", head->opernand);
        printf("%d ", head->prior);
        head = head->next;
        printf("\n");

    }
    printf("\n");
}
