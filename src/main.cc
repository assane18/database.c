test#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  // Pour ssize_t
#include "repl.h"      // Inclure les déclarations des fonctions de REPL
#include "table.h"     // Inclure les déclarations des fonctions de la table

int main() {
    // Définir les colonnes de la table
    Colonne columns[4] = {
        {"ID", TYPE_COLONNE_INT},        // Colonne pour ID (entier)
        {"Nom", TYPE_COLONNE_TEXTE},     // Colonne pour le nom (texte)
        {"Prenom", TYPE_COLONNE_TEXTE},  // Colonne pour le prénom (texte)
        {"Age", TYPE_COLONNE_INT}        // Colonne pour l'âge (entier)
    };

    // Créer une table nommée "Personnes" avec 4 colonnes
    Table* table = creer_table("Personnes", 4, columns);
    if (table == NULL) {
        fprintf(stderr, "Erreur lors de la création de la table.\n");
        return EXIT_FAILURE; // Sortir si la table n'a pas pu être créée
    }

    // Lancer la boucle REPL (pour les commandes "insert" et "select")
    printf("Bienvenue dans le gestionnaire de base de données !\n");
    repl(table);

    // Libérer la mémoire à la fin du programme
    liberer_table(table); // Libérer la mémoire allouée pour la table

    return EXIT_SUCCESS; // Retourner 0 pour indiquer que le programme s'est terminé avec succès
}
