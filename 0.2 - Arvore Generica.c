#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    void *data;
    struct node *left, *right;
}node;

typedef struct integer{
    int data;
}integer;

node *createNode(void *value){
    node *newNode = (node *)calloc(1, sizeof(node));
    if(!newNode){ printf("ERROR"); exit(1); }
    newNode->data = value;
    return newNode;
}

node *insertNode(node *root, void *value) {
    if (root == NULL) return createNode(value);

    integer *currentInt = (integer *)root->data;
    integer *newInt = (integer *)value;

    if (newInt->data < currentInt->data) root->left = insertNode(root->left, value);
    else root->right = insertNode(root->right, value);
    return root;
}

void imprimeArvore(node *root, void (*callback)(void *)) {
    if (root != NULL) {
        imprimeArvore(root->left, callback);
        callback(root->data);
        imprimeArvore(root->right, callback);
    }
}

void imprimeInt(void *I) {
    integer *inteiro = (integer *)I;
    printf("%d ", inteiro->data);
}

node *insertInteger(node *root, int value) {
    integer *inteiro = (integer *)calloc(1, sizeof(integer));
    if (!inteiro) { 
        printf("ERROR"); 
        exit(1); 
    }
    inteiro->data = value;
    return insertNode(root, inteiro);
}

int main(void) {
    node *root = NULL;

    root = insertInteger(root, 5);
    root = insertInteger(root, 3);
    root = insertInteger(root, 7);
    root = insertInteger(root, 2);
    root = insertInteger(root, 4);
    root = insertInteger(root, 6);
    root = insertInteger(root, 8);

    printf("Inorder Traversal: ");
    imprimeArvore(root, imprimeInt);
    printf("\n");

    return 0;
}