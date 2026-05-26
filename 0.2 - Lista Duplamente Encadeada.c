#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next, *prev;
} node;

node *createNode(int data) {
    node* newNode = (node*)calloc(1, sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    return newNode;
}

void push(node **list, int data) {
    node *newNode = createNode(data);
    if (*list == NULL) {
        *list = newNode;
    } else {
        node *aux = *list;
        while (aux->next != NULL) aux = aux->next;
        aux->next = newNode;
        newNode->prev = aux;
    }
}

void pop(node **list) {
    if (*list == NULL) return;
    if ((*list)->next == NULL) {
        free(*list);
        *list = NULL;
    } else {
        node *aux = *list;
        while (aux->next != NULL) aux = aux->next;
        aux->prev->next = NULL;
        free(aux);
    }
}

void insertOrdered(node **list, int data) {
    node *newNode = createNode(data);
    node *aux = *list;
    node *prev = NULL;
    while (aux != NULL && aux->data < data) {
        prev = aux;
        aux = aux->next;
    }
    if (prev == NULL) {
        newNode->next = *list;
        if (*list != NULL) (*list)->prev = newNode;
        *list = newNode;
    } else {
        prev->next = newNode;
        newNode->prev = prev;
        newNode->next = aux;
        if (aux != NULL) aux->prev = newNode;
    }
}

void deleteOrdered(node **list, int data) {
    if (*list == NULL) return;
    node *aux = *list;
    while (aux != NULL && aux->data != data) aux = aux->next;
    if (aux == NULL) return;
    if (aux->prev != NULL) aux->prev->next = aux->next;
    else *list = aux->next;
    if (aux->next != NULL) aux->next->prev = aux->prev;
    free(aux);
}

void printList(node *list) {
    if(list == NULL) {
        printf("Lista vazia\n");
        return;
    }
    node *aux = list;
    printf("NULL <- ");
    while (aux->next != NULL) {
        printf("%d <-> ", aux->data);
        aux = aux->next;
    }
    printf("%d -> NULL\n", aux->data);
}

int main() {
    node *myList = NULL;
    push(&myList, 10);
    push(&myList, 20);
    push(&myList, 30);
    printList(myList);
    pop(&myList);
    printList(myList);
    insertOrdered(&myList, 25);
    printList(myList);
    deleteOrdered(&myList, 20);
    printList(myList);
    return 0;
}