#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *left, *right;
} tree;

tree *createRoot(int value){
    tree *newRoot = (tree *)calloc(1, sizeof(tree));
    if(!newRoot){ printf("ERROR!"); exit(1); }
    newRoot->data = value;
    return newRoot;
}

void insertNode(tree **T, int value){
    tree *newRoot = createRoot(value);
    if(!(*T)) *T = newRoot;
    else{
        tree *aux = (*T);
        tree *pai = NULL;
        while(aux != NULL){
            if(value == aux->data) return;
            if(value > aux->data){ pai = aux; aux = aux->right; }
            else{ pai = aux; aux = aux->left; }
        }
        if(value > pai->data) pai->right = newRoot;
        else pai->left = newRoot;
    }
}

tree *searchMax(tree *T){
    while(T->left != NULL) T = T->left;
    return T;
}

void deleteNode(tree **T, int value){
    if(!(*T)) return;
    tree *aux = (*T);
    tree *pai = NULL;
    while(aux != NULL){
        if(aux->data == value) break;
        pai = aux;
        if(value > aux->data) aux = aux->right;
        else aux = aux->left;
    }
    if(!aux) return;
    if(aux->data == value){ 
        if(!aux->left && !aux->right){ // Caso 1
            if(aux == pai->left) pai->left = NULL;
            else if(aux == pai->right) pai->right = NULL;
            free(aux);
        } else if(!aux->left || !aux->right){ // Caso 2
            if(aux->right != NULL && aux->left == NULL){
                if(aux == pai->right) pai->right = aux->right;
                else if(aux == pai->left) pai->left = aux->right;
                free(aux);
            } else if(aux->right == NULL && aux->left != NULL){
                if(aux == pai->right) pai->right = aux->left;
                else if(aux == pai->left) pai->left = aux->left;
                free(aux);
            }
        } else if(aux->left != NULL && aux->right != NULL){ // Caso 3
            tree *temp = searchMax(aux->right);
            int tempValue = temp->data;
            deleteNode(&(*T), tempValue);
            aux->data = tempValue;
        }
    }
}

void printTree(tree *T){
    if(!T) return;
    printf("%d ", T->data);
    printTree(T->left);
    printTree(T->right);
}

int main(void){
    tree *root = NULL;
    insertNode(&root, 5);
    insertNode(&root, 3);
    insertNode(&root, 7);
    insertNode(&root, 2);
    insertNode(&root, 4);
    insertNode(&root, 6);
    insertNode(&root, 8);
    insertNode(&root, 9);
    insertNode(&root, 10);
    insertNode(&root, -1);
    printTree(root);
    printf("\n");
    deleteNode(&root, -1);
    printTree(root);
    printf("\n");
    deleteNode(&root, 9);
    printTree(root);
    printf("\n");
    deleteNode(&root, 10);
    printTree(root);
    printf("\n");
    deleteNode(&root, 3);
    printTree(root);

    return 0;
}