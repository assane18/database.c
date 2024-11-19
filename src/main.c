#include <stdio.h>
#include <stdlib.h>
#include "repl.h"
#include "table.h"

// Point d'entrée du programme
int main() {
    // Définition des colonnes pour la table "Personnes"
    Colonne columns[4] = {
        {"ID", TYPE_COLONNE_INT},
        {"Nom", TYPE_COLONNE_TEXTE},
        {"Prenom", TYPE_COLONNE_TEXTE},
        {"Age", TYPE_COLONNE_INT}
    };

    // Création de la table
    Table* table = creer_table("Personnes", 4, columns);
    if (table == NULL) {
        fprintf(stderr, "Erreur lors de la création de la table.\n");
        return EXIT_FAILURE; // Quitte le programme si la table n'a pas pu être créée
    }

    // Démarrage de la boucle REPL pour interagir avec l'utilisateur
    printf("Bienvenue dans le gestionnaire de base de données !\n");
    repl(table);

    // Libération de la mémoire avant de quitter
    liberer_table(table);

    return EXIT_SUCCESS; // Indique que le programme s'est terminé correctement
}