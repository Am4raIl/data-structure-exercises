#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int coef, exp;
    struct node *next;
}node;

node *createNode(int cfc, int expt){
    node *newNode = (node *)calloc(1, sizeof(node));
    if(!newNode){ printf("ERROR!"); exit(1); }
    newNode->coef = cfc;
    newNode->exp = expt;
    return newNode;
}

void insertNode(node **L, int coeficiente, int expoente){
    node *newNode = createNode(coeficiente, expoente);
    node *aux = (*L);
    if(!(*L)) (*L) = newNode;
    else{
        while(aux->next != NULL) aux = aux->next;
        aux->next = newNode;
    }
}

void printList(node *L){
    if(!L) return;
    node *aux = L;
    while(aux){
        printf("%d^%d ", aux->coef, aux->exp);
        aux = aux->next;
    }
}

node *sumP(node *L1, node *L2){
    node *L3 = NULL;
    if(!L1 && !L2) return L3;
    if(!L1) return L2;
    if(!L2) return L1;
    node *aux1 = L1, *aux2 = L2;
    while(aux1 || aux2){
        if(!aux1 && !aux2) return L3;
        if(!aux1){ insertNode(&L3, aux2->coef, aux2->exp); aux2 = aux2->next; }
        else if(!aux2){ insertNode(&L3, aux1->coef, aux1->exp); aux1 = aux1->next; }
        else{
            if(aux1->exp > aux2->exp){
                insertNode(&L3, aux2->coef, aux2->exp);
                aux2 = aux2->next;
            } else if(aux1->exp < aux2->exp){
                insertNode(&L3, aux1->coef, aux1->exp);
                aux1 = aux1->next;
            } else{
                insertNode(&L3, aux1->coef + aux2->coef, aux1->exp);
                aux1 = aux1->next;
                aux2 = aux2->next;
            }
        }
    }
    return L3;
}

int main(void){
    node *L1 = NULL, *L2 = NULL;
    insertNode(&L1, 2, 3);
    insertNode(&L1, 6, 2);
    insertNode(&L1, 4, 4);
    printList(L1);

    printf("\n");
    insertNode(&L2, 5, 2);
    insertNode(&L2, 3, 4);
    insertNode(&L2, 5, 3);
    insertNode(&L2, 2, 1);
    printList(L2);

    printf("\n");
    node *L3 = sumP(L1, L2);
    printList(L3);

    return 0;
}