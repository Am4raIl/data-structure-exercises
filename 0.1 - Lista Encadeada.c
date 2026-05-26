#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node *createNode(int data){
    node *newNode = (node *)calloc(1, sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    return newNode;
}

void push(node **list, int data){
    node *newNode = createNode(data);
    if(*list == NULL) *list = newNode;
    else {
        node *aux = *list;
        while(aux->next != NULL) aux = aux->next;
        aux->next = newNode;
    }
}

void pop(node **list){
    if(*list == NULL) return;
    if((*list)->next == NULL){
        free(*list);
        *list = NULL;
    } else {
        node *aux = *list;
        while(aux->next->next != NULL) aux = aux->next;
        free(aux->next);
        aux->next = NULL;
    }
}

void insertOrdered(node **list, int data){
    node *newNode = createNode(data);
    node *aux = *list;
    node *prev = NULL;
    while(aux != NULL && aux->data < data) {
        prev = aux;
        aux = aux->next;
    }
    if(prev == NULL) {
        newNode->next = *list;
        *list = newNode;
    } 
    else {
        prev->next = newNode;
        newNode->next = aux;
    }
}

void deleteOrdened(node **list, int data){
    if(*list == NULL) return;
    node *aux = *list;
    node *prev = NULL;
    while(aux != NULL && aux->data != data) {
        prev = aux;
        aux = aux->next;
    }
    if(aux == NULL) return; 
    if(prev == NULL) *list = aux->next;
    else prev->next = aux->next;
    free(aux);
}

void printList(node *list){
    if(list == NULL) {
        printf("Lista vazia\n");
        return;
    }
    node *aux = list;
    while(aux != NULL){
        printf("%d -> ", aux->data);
        aux = aux->next;
    }
    printf("NULL\n");
}

int main(void){
    node *myList = NULL;
    push(&myList, 10);
    push(&myList, 20);
    push(&myList, 30);
    printList(myList);
    pop(&myList);
    printList(myList);
    insertOrdered(&myList, 25);
    printList(myList);
    deleteOrdened(&myList, 20);
    printList(myList);
    return 0;
}