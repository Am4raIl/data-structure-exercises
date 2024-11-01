#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int color; // 0 para negro, 1 para rubro
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

// Função para realizar uma rotação à esquerda
void rotateLeft(Node **T, Node *w) {
    Node *v = w->right;
    w->right = v->left;
    
    if (v->left != NULL) v->left->parent = w;
    
    v->parent = w->parent;
    
    if (w->parent == NULL) *T = v;
    else if (w == w->parent->left) w->parent->left = v;
    else w->parent->right = v;
    
    v->left = w;
    w->parent = v;
}

// Função para realizar uma rotação à direita
void rotateRight(Node **T, Node *w) {
    Node *v = w->left;
    w->left = v->right;
    
    if (v->right != NULL) v->right->parent = w;
    
    v->parent = w->parent;
    
    if (w->parent == NULL) *T = v;
    else if (w == w->parent->right) w->parent->right = v;
    else w->parent->left = v;
    
    v->right = w;
    w->parent = v;
}

// Função para corrigir a árvore após a inserção
void RBInsertFixup(Node **T, Node *q) {
    Node *v, *w, *t;
    
    while (q->parent != NULL && q->parent->color == 1) {
        v = q->parent;
        w = v->parent;
        if (v == w->left) {
            t = w->right; 
            if (t != NULL && t->color == 1) { // Caso 1
                v->color = t->color = 0;
                w->color = 1;
                q = w;
            } else {
                if (q == v->right) { // Caso 2
                    q = v;
                    rotateLeft(T, q);
                }
                q->parent->color = 0;
                w->color = 1; // Caso 3
                rotateRight(T, w);
            }
        } else {
            t = w->left;
            if (t != NULL && t->color == 1) { // Caso 1
                v->color = t->color = 0;
                w->color = 1;
                q = w;
            } else {
                if (q == v->left) { // Caso 2
                    q = v;
                    rotateRight(T, q);
                }
                q->parent->color = 0;
                w->color = 1; // Caso 3
                rotateLeft(T, w);
            }
        }
    }
    
    (*T)->color = 0;
}

// Função para inserir um nó na árvore rubro-negra
void RBInsert(Node **T, Node *q) {
    Node *aux = *T;
    Node *v = NULL;
    
    while (aux != NULL) {
        v = aux;
        if (q->key == aux->key) return;
        else if (q->key < aux->key) aux = aux->left;
        else aux = aux->right;
    }
    
    q->parent = v;
    
    if (v == NULL) *T = q;
    else if (q->key < v->key) v->left = q;
    else v->right = q;
    
    q->left = q->right = NULL;
    q->color = 1; // Novo nó é rubro
    RBInsertFixup(T, q);
}
