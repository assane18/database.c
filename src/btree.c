#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

// Créer un nouveau nœud avec une valeur donnée
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Erreur d'allocation mémoire pour le nœud");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->left = new_node->right = NULL;
    return new_node;
}

// Insérer une valeur dans l'arbre binaire de recherche
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

// Rechercher une valeur dans l'arbre
Node* search(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

// Fonction pour effectuer une rotation à gauche
Node* rotate_left(Node* root) {
    Node* new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    return new_root;
}

// Fonction pour effectuer une rotation à droite
Node* rotate_right(Node* root) {
    Node* new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    return new_root;
}

// Fonction d'équilibrage de l'arbre
Node* balance(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left == NULL && root->right != NULL) {
        root = rotate_left(root);
    } else if (root->right == NULL && root->left != NULL) {
        root = rotate_right(root);
    }

    return root;
}

// Traversée en ordre (in-order) pour afficher les valeurs de l'arbre
void inorder_traversal(Node* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

// Libérer la mémoire de l'arbre
void free_tree(Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

// Sauvegarder l'arbre dans un fichier binaire
void save_tree(Node* root, FILE* file) {
    if (root == NULL) {
        int null_indicator = 0;
        fwrite(&null_indicator, sizeof(int), 1, file);
        return;
    }

    fwrite(&root->data, sizeof(int), 1, file);
    save_tree(root->left, file);
    save_tree(root->right, file);
}

// Charger l'arbre depuis un fichier binaire
Node* load_tree(FILE* file) {
    int data;
    
    if (fread(&data, sizeof(int), 1, file) != 1) {
        return NULL; 
    }

    if (data == 0) {
        return NULL;
    }

    Node* new_node = create_node(data);
    new_node->left = load_tree(file);
    new_node->right = load_tree(file);

    return new_node;
}
