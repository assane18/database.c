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

// Fonction pour créer un nouveau nœud
Node* create_node(int data);

// Fonction pour insérer une valeur dans l'arbre
Node* insert(Node* root, int data, void* line);

// Fonction pour rechercher une valeur dans l'arbre
Node* search(Node* root, int data);

#endif // BTREE_H
