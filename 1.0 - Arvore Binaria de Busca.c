#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree{
    int data;
    struct tree *left, *right;
}tree;

tree *createTree(int value){
    tree *newNode = (tree *)calloc(1, sizeof(tree));
    if(!newNode){ printf("ERROR"); exit(1); }
    newNode->data = value;
    return newNode;
}

tree *searchNode(tree *T, int value){
    if(!T) return NULL;
    tree *aux = T;
    while(aux != NULL && aux->data != value){
        if(aux->data < value) aux = aux->right;
        else if(aux->data > value) aux = aux->left;
    }
    return aux;
}

void insertNode(tree **T, int value){
    tree *newNode = createTree(value);
    tree *aux = (*T);
    if(!(*T)) (*T) = newNode;
    else {
        tree *pai = NULL;
        while(aux != NULL){
            pai = aux;
            if(value < aux->data) aux = aux->left;
            else if(value > aux->data) aux = aux->right;
            else { printf("Valor ja presente na arvore"); return; }
        }
        if(value < pai->data) pai->left = newNode;
        else if(value > pai->data) pai->right = newNode;
        else { printf("Valor ja presente na arvore"); return; }
    }
}

tree *sucessor(tree *node) {
    while (node->left != NULL) node = node->left;
    return node;
}

void deleteNode(tree **T, int value) {
    if (*T == NULL) return;
    tree *pai = NULL;
    tree *aux = *T;
    while (aux != NULL && aux->data != value) {
        pai = aux;
        if (value < aux->data) aux = aux->left;
        else aux = aux->right;
    }
    if (aux == NULL) return;
    // Case 1
    if (aux->left == NULL && aux->right == NULL) {
        if (aux == *T) *T = NULL;
        else if (aux == pai->left) pai->left = NULL;
        else pai->right = NULL;
        free(aux);
    }
    // Case 2
    else if (aux->left == NULL || aux->right == NULL) {
        tree *child = (aux->left != NULL) ? aux->left : aux->right;
        if (aux == *T) *T = child;
        else if (aux == pai->left) pai->left = child;
        else pai->right = child;
        free(aux);
    }
    // Case 3
    else {
        tree *successor = sucessor(aux->right);
        int successorValue = successor->data;
        deleteNode(&(*T), successorValue); 
        aux->data = successorValue;
    }
}

void printTreeSim(tree *T){
    if(T == NULL) return;
    printTreeSim(T->left);
    printf("%d ", T->data);
    printTreeSim(T->right);
}

void printTreePre(tree *T){
    if(T == NULL) return;
    printf("%d ", T->data);
    printTreePre(T->left);
    printTreePre(T->right);
}

void printTreePos(tree *T){
    if(T == NULL) return;
    printTreePos(T->left);
    printTreePos(T->right);
    printf("%d ", T->data);
}

int main(void){
    tree *T = NULL;
    insertNode(&T, 5);
    insertNode(&T, 3);
    insertNode(&T, 7);
    insertNode(&T, 4);
    insertNode(&T, 6);
    insertNode(&T, 2);
    insertNode(&T, 8);
    insertNode(&T, 9);
    insertNode(&T, 10);
    insertNode(&T, 11);
    printTreePre(T);
    printf("\n");
    printTreeSim(T);
    printf("\n");
    printTreePos(T);
    printf("\n");
    deleteNode(&T, 3);
    deleteNode(&T, 8);
    printTreeSim(T);

    return 0;
}