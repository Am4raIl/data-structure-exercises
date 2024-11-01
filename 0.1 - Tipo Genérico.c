#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    void *data;
    struct node *next;
}node;

typedef struct integer{
    int data;
}integer;

typedef struct point{
    int x, y;
}point;

node *createNode(void *value){
    node *newNode = (node *)calloc(1, sizeof(node));
    if(!newNode){ printf("ERROR"); exit(1); }
    newNode->data = value;
    return newNode;
}

node *insertNode(node *L, void *value){
    node *newNode = createNode(value);
    newNode->next = L;
    return newNode;
}

void percorreLista(node *L, void (*callback)(void *)){
    node *aux = L;
    while(aux != NULL){
        callback(aux->data);
        aux = aux->next;
    }
}

node *insertInteger(node *L, int value){
    integer *inteiro = (integer *)calloc(1, sizeof(integer));
    if(!inteiro){ printf("ERROR"); exit(1); }
    inteiro->data = value;
    return insertNode(L, inteiro);
}

void imprimeInt(void *I){
    integer *inteiro = (integer *)I;
    printf("%d ", inteiro->data);
}

node *insertPoint(node *L, int x, int y){
    point *xpto = (point *)calloc(1, sizeof(point));
    if(!xpto){ printf("ERROR"); exit(1); }
    xpto->x = x;
    xpto->y = y;
    return insertNode(L, xpto);
}

void imprimePonto(void *P){
    point *xpto = (point *)P;
    printf("[%d, %d] ", xpto->x, xpto->y);
}

int main(void){
    node *L = NULL;
    L = insertInteger(L, 5);
    L = insertInteger(L, 4);
    L = insertInteger(L, 3);
    L = insertInteger(L, 2);
    L = insertInteger(L, 1);
    percorreLista(L, imprimeInt);
    printf("\n");
    L = insertPoint(L, 3, 4);
    L = insertPoint(L, 5, 2);
    L = insertPoint(L, 1, 1);
    percorreLista(L, imprimePonto);
    printf("\n");
    percorreLista(L, imprimeInt);
    printf("\n");

    return 0;
}