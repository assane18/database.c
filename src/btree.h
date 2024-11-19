#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>

// Structure du nœud de l'arbre binaire
typedef struct Node {
    int data;           // Valeur du nœud (ici on utilise l'ID de la ligne)
    void* line;         // Pointeur vers la ligne entière (les données de l'enregistrement)
    struct Node* left;  // Pointeur vers le sous-arbre gauche
    struct Node* right; // Pointeur vers le sous-arbre droit
} Node;

// Prototypes de fonctions pour manipuler l'arbre binaire
Node* create_node(int data);
Node* insert(Node* root, int data, void* line);
Node* search(Node* root, int data);

#endif // BTREE_H