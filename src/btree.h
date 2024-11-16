#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>

// Structure du nœud de l'arbre binaire
typedef struct Node {
    int data;           // Valeur du nœud
    struct Node* left;  // Pointeur vers le sous-arbre gauche
    struct Node* right; // Pointeur vers le sous-arbre droit
} Node;

// Fonction pour créer un nouveau nœud
Node* create_node(int data);

// Fonction pour insérer une valeur dans l'arbre
Node* insert(Node* root, int data);

// Fonction pour rechercher une valeur dans l'arbre
Node* search(Node* root, int data);

// Fonction pour effectuer une rotation à gauche (équilibrage simple)
Node* rotate_left(Node* root);

// Fonction pour effectuer une rotation à droite (équilibrage simple)
Node* rotate_right(Node* root);

// Fonction pour équilibrer l'arbre (en effectuant des rotations simples)
Node* balance(Node* root);

// Fonction pour effectuer une traversée en ordre de l'arbre
void inorder_traversal(Node* root);

// Fonction pour libérer la mémoire de l'arbre
void free_tree(Node* root);

// Fonction pour sauvegarder l'arbre dans un fichier binaire
void save_tree(Node* root, FILE* file);

// Fonction pour charger un arbre depuis un fichier binaire
Node* load_tree(FILE* file);

#endif // BTREE_H
