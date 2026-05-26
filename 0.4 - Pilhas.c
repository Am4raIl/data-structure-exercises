#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next; 
} node;

typedef struct stack{
    node *top;
} stack;

node* createNode(int data){
    node *newNode = (node *)calloc(1, sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    return newNode;
}

stack* createStack(int data){
    node *newNode = createNode(data);
    stack *newStack = (stack *)calloc(1, sizeof(stack));
    if (newStack == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newStack->top = newNode;
    return newStack;
}

void stackup(stack *stack, int data){
    node *newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

void unstack(stack *stack){
    if(stack->top == NULL) return;
    node *aux = stack->top;
    stack->top = stack->top->next;
    free(aux);
}

void printStack(stack *stack){
    if(stack->top == NULL) {
        printf("Pilha vazia\n");
        return;
    }
    node *aux = stack->top;
    while(aux != NULL){
        printf("%d -> ", aux->data);
        aux = aux->next;
    }
    printf("NULL\n");
}

int main(){
    stack *myStack = createStack(10);
    stackup(myStack, 20);
    stackup(myStack, 30);
    printStack(myStack);
    unstack(myStack);
    printStack(myStack);
    return 0;
}