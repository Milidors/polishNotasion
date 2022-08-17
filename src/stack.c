#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
----------------------MADE Milidors----------------------
------------------------2  0  2  2----------------------
*/

/*
----------------------ОСТАЛОСЬ ДОБАВИТЬ----------------------
1) Работа со скобками +++++++++++
2)Работа с минусом +++++++++++
3)добавление математических функций ----------
4)Работа программы без остановки +++++++++++
5)Доработать округлени ----------
6)ОЧИСТКА ПАМЯТИ ???????????
7)Проверка на корректность введенных данных ----------
----------------------КОНЕЦ----------------------
*/

// Инициализация стtека
stack *initStack(int prior, char opernand) {
    stack* tmp = (stack*)malloc(sizeof(stack));
    tmp -> prior = prior;
    tmp -> opernand = opernand;
    tmp -> next = NULL;
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
void pushQueue(float num, queue** head) {
    queue* tmp = (queue*)malloc(sizeof(queue));
    tmp->number = num;
    tmp->next = (*head);
    (*head) = tmp;
}
// Удаление и вывод элементов из стека
float popQueue(queue** head){
    queue* tmp = NULL;
    float value = 0;
    if (head == NULL) {
        exit(-1);
    }
    tmp = (*head);
    value = tmp ->number;
    (*head) = (*head)->next;
    free(tmp);
    return value;
}
// Удаление и вывод элементов из стека

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
void deleteFirstElementInStack(stack** head) {
    stack* tmp = NULL;
    if (head == NULL) {
        exit(-1);
    }
    tmp = (*head);
    (*head) = (*head)->next;
    free(tmp);
}
// Вывод всех эл-тов в очереди
void printLinkedListQueue(queue *head) {
    while (head != NULL) {
        printf("%.10f ", head->number);
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

int sizeQueue(queue* head) {
    int size = 0; 
    while (head != NULL) {
        size += 1;
        head = head->next;
        }
    return size;
}

int sizeStack(stack* head) {
    int size = 0; 
    while (head != NULL) {
        size += 1;
        head = head->next;
        }
    return size;
}

void deleteQueue(queue** head) {
    while ((*head) -> next)
    {
        popQueue(head);
        *head = (*head) ->next;
    }
    free(*head);
}
void deleteStack(stack** head) {
while ((*head) -> next)
    {
        popStack(head);
        *head = (*head) ->next;
    }
    free(*head);
}
