#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

int main() {
    // Créer un arbre binaire et insérer quelques valeurs
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 30);
    
    // Afficher l'arbre avant la sauvegarde
    printf("Arbre avant la sauvegarde : ");
    inorder_traversal(root);
    printf("\n");

    // Sauvegarder l'arbre dans un fichier
    FILE* file = fopen("save_tree.bin", "wb");
    if (file == NULL) {
        perror("Erreur lors de la création du fichier de sauvegarde");
        return EXIT_FAILURE;
    }
    save_tree(root, file);
    fclose(file);
    printf("Arbre sauvegardé dans 'save_tree.bin'.\n");

    // Charger l'arbre depuis le fichier
    file = fopen("save_tree.bin", "rb");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sauvegarde");
        return EXIT_FAILURE;
    }
    Node* loaded_tree = load_tree(file);
    fclose(file);

    // Afficher l'arbre après le chargement
    printf("Arbre chargé : ");
    inorder_traversal(loaded_tree);
    printf("\n");

    // Libérer la mémoire allouée pour les arbres
    free_tree(root);
    free_tree(loaded_tree);

    return EXIT_SUCCESS;
}
