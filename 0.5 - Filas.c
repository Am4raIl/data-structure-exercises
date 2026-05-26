#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
} node;

typedef struct queue{
    node *front;
    node *rear;
} queue;

node* createNode(int data){
    node *newNode = (node *)calloc(1, sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    return newNode;
}

queue* createQueue(int data){
    node *newNode = createNode(data);
    queue *newQueue = (queue *)calloc(1, sizeof(queue));
    if (newQueue == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newQueue->front = newNode;
    newQueue->rear = newNode;
    return newQueue;
}

void enqueue(queue *queue, int data){
    node *newNode = createNode(data);
    if(queue->front == NULL && queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;

    }
}

void dequeue(queue *queue){
    if(queue->front == NULL && queue->rear == NULL) return;
    node *aux = queue->front;
    queue->front = queue->front->next;
    if(queue->front == NULL) queue->rear = NULL;
    free(aux);
}

void printQueue(queue *queue){
    if(queue->front == NULL) {
        printf("Fila vazia\n");
        return;
    }
    node *aux = queue->front;
    while(aux != NULL){
        printf("%d -> ", aux->data);
        aux = aux->next;
    }
    printf("NULL\n");
}

int main(){
    queue *myQueue = createQueue(10);
    enqueue(myQueue, 20);
    enqueue(myQueue, 30);
    printQueue(myQueue);
    dequeue(myQueue);
    printQueue(myQueue);
}