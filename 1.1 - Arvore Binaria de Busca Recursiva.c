#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree{
    int data;
    struct tree *left, *right;
}tree;

tree *createRoot(int value){
    tree *newNode = (tree *)calloc(1, sizeof(tree));
    if(!newNode){ printf("ERROR"); exit(1); }
    newNode->data = value;
    return newNode;
}

tree *searchRoot(tree *T, int value){
    if(!T) return T;
    if(value > T->data) return searchRoot(T->right, value);
    else if(value < T->data) return searchRoot(T->left, value);
    return T;
}

void insertNode(tree **T, int value){
    if(!(*T)) (*T) = createRoot(value);
    if(value > (*T)->data) insertNode(&(*T)->right, value);
    else if(value < (*T)->data) insertNode(&(*T)->left, value);
    else printf("Valor ja existe na arvore.");
}

tree *findSucessor(tree *T) {
    while (T->left != NULL) T = T->left;
    return T;
}

void removeNode(tree **T, int value) {
    if (!(*T)) return;
    if (value < (*T)->data) removeNode(&(*T)->left, value);
    else if (value > (*T)->data) removeNode(&(*T)->right, value);
    else {
        tree *temp;
        if (!(*T)->left) { // Caso 1
            temp = *T;
            *T = (*T)->right;
            free(temp);
        } else if (!(*T)->right) { // Caso 2
            temp = *T;
            *T = (*T)->left;
            free(temp);
        } else { // Caso 3
            temp = findSucessor((*T)->right);
            (*T)->data = temp->data;
            removeNode(&(*T)->right, temp->data);
        }
    }
}

void printTreeSim(tree *T){
    if(T == NULL) return;
    printTreeSim(T->left);
    printf("%d ", T->data);
    printTreeSim(T->right);
}

int main(void){
    tree *T = NULL;
    insertNode(&T, 5);
    insertNode(&T, 3);
    insertNode(&T, 7);
    printTreeSim(T);

    return 0;
}