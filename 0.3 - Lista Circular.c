#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

node* createNode(int data) {
    node* newNode = (node*)calloc(1, sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = newNode;
    return newNode;
}

void push(node** list, int data) {
    node* newNode = createNode(data);
    if (*list == NULL) {
        *list = newNode;
    } else {
        node* aux = *list;
        while (aux->next != *list) aux = aux->next;
        aux->next = newNode;
        newNode->next = *list;
    }
}

void pop(node** list) {
    if (*list == NULL) return;
    if ((*list)->next == *list) {
        free(*list);
        *list = NULL;
    } else {
        node* aux = *list;
        while (aux->next != *list) aux = aux->next;
        node* toDelete = *list;
        aux->next = (*list)->next;
        *list = (*list)->next;
        free(toDelete);
    }
}

void insertOrdered(node** list, int data) {
    node* newNode = createNode(data);
    if (*list == NULL) {
        *list = newNode;
    } else {
        node* aux = *list;
        node* prev = NULL;
        do {
            if (aux->data >= data) break;
            prev = aux;
            aux = aux->next;
        } while (aux != *list);
        if (prev == NULL) {
            newNode->next = *list;
            node* last = *list;
            while (last->next != *list) last = last->next;
            last->next = newNode;
            *list = newNode;
        } else {
            prev->next = newNode;
            newNode->next = aux;
        }
    }
}

void deleteOrdered(node** list, int data) {
    if (*list == NULL) return;
    node* aux = *list;
    node* prev = NULL;
    do {
        if (aux->data == data) break;
        prev = aux;
        aux = aux->next;
    } while (aux != *list);
    if (aux->data != data) return; 
    if (prev == NULL) {
        node* last = *list;
        while (last->next != *list) last = last->next;
        if (last == *list) {
            free(*list);
            *list = NULL;
        } else {
            last->next = (*list)->next;
            node* toDelete = *list;
            *list = (*list)->next;
            free(toDelete);
        }
    } else {
        prev->next = aux->next;
        free(aux);
    }
}

void printList(node* list) {
    if(list == NULL) {
        printf("Lista vazia\n");
        return;
    }
    node* aux = list;
    do {
        printf("%d -> ", aux->data);
        aux = aux->next;
    } while (aux != list);
    printf("(de volta para %d)\n", list->data);
    printf("\n");
}

int main() {
    node* myList = NULL;
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