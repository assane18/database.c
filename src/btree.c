#include "btree.h"
#include <stdlib.h>

// Fonction pour créer un nouveau nœud
Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->line = NULL;
    return node;
}

// Fonction pour insérer une valeur dans l'arbre
Node* insert(Node* root, int data, void* line) {
    if (root == NULL) {
        Node* node = create_node(data);
        node->line = line; // Assigner la ligne à ce nœud
        return node;
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data, line);
    } else if (data > root->data) {
        root->right = insert(root->right, data, line);
    }

    return root;
}

// Fonction pour rechercher une valeur dans l'arbre
Node* search(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    }
    
    return search(root->right, data);
}
