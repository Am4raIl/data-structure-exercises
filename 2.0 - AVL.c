#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int data, balance;
    struct tree *left, *right;
} tree;

tree* createNode(int value) {
    tree *newNode = (tree *)calloc(1, sizeof(tree));
    if (!newNode) { 
        printf("ERROR\n"); 
        exit(1); 
    }
    newNode->data = value;
    newNode->balance = 0;
    return newNode;
}

void rightRotation(tree **T, int *height) {
    tree *u, *z;
    u = (*T)->left;

    if (u->balance == 1) { // Simple Right Rotation
        (*T)->left = u->right;
        u->right = *T;
        (*T)->balance = 0;
        *T = u;
    } else { // Double Right Rotation
        z = u->right;
        u->right = z->left;
        z->left = u;
        (*T)->left = z->right;
        z->right = *T;

        if (z->balance == 1) (*T)->balance = -1;
        else (*T)->balance = 0;
        if (z->balance == -1) u->balance = 1;
        else u->balance = 0;

        *T = z;
    }
    (*T)->balance = 0;
    *height = 1;
}

void leftRotation(tree **T, int *height) {
    tree *u, *z;
    u = (*T)->right;

    if (u->balance == -1) { // Simple Left Rotation
        (*T)->right = u->left;
        u->left = *T;
        (*T)->balance = 0;
        *T = u;
    } else { // Double Left Rotation
        z = u->left;
        u->left = z->right;
        z->right = u;
        (*T)->right = z->left;
        z->left = *T;

        if (z->balance == -1) (*T)->balance = 1;
        else (*T)->balance = 0;
        if (z->balance == 1) u->balance = -1;
        else u->balance = 0;

        *T = z;
    }
    (*T)->balance = 0;
    *height = 1;
}

void insertAVL(tree **T, int *height, int value) {
    if (*T == NULL) {
        *T = createNode(value);
        *height = 1;
        return;
    }
    if (value < (*T)->data) {
        insertAVL(&(*T)->left, height, value);
        if (*height) {
            switch ((*T)->balance){
                case -1:
                    (*T)->balance = 0;
                    *height = 0;
                    break;
                case 0:
                    (*T)->balance = 1;
                    break;
                case 1:
                    rightRotation(T, height);
                    break;
            }
        }
    } else if (value > (*T)->data) {
        insertAVL(&(*T)->right, height, value);
        if (*height) {
            switch ((*T)->balance) {
                case 1:
                    (*T)->balance = 0;
                    *height = 0;
                    break;
                case 0:
                    (*T)->balance = -1;
                    break;
                case -1:
                    leftRotation(T, height);
                    break;
            }
        }
    }
}

void printTree(tree *v) {
    if (v != NULL) {
        printTree(v->left);
        printf("%d ", v->data);
        printTree(v->right);
    }
}

int main() {
    tree *root = NULL;
    int height = 0;
    
    insertAVL(&root, &height, 5);
    insertAVL(&root, &height, 7);
    insertAVL(&root, &height, 3);
    printTree(root);
    printf("\n");

    insertAVL(&root, &height, 8);
    printTree(root);
    printf("\n");

    insertAVL(&root, &height, 9);
    printTree(root);
    printf("\n");

    return 0;
}
