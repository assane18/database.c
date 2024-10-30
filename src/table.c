#include "table.h"
#include <stdio.h>  // Inclure pour les fonctions d'affichage (printf)
#include <stdlib.h> // Inclure pour malloc et realloc
#include <string.h> // Inclure pour strncpy et memcpy

// Fonction pour créer une nouvelle table
Table* creer_table(const char* nom, int nb_colonnes, Colonne* colonnes) {
    if (nb_colonnes <= 0 || colonnes == NULL) {
        return NULL; // Retourner NULL si les arguments sont invalides
    }

    Table* table = (Table*)malloc(sizeof(Table));  // Allouer de la mémoire pour la table
    if (table == NULL) {
        return NULL;  // Retourner NULL si l'allocation échoue
    }

    // Copier le nom de la table
    strncpy(table->nom, nom, MAX_LONGUEUR_NOM);
    table->nom[MAX_LONGUEUR_NOM - 1] = '\0'; // S'assurer que le nom est null-terminé

    // Initialiser les colonnes et lignes
    table->nb_colonnes = nb_colonnes;
    table->colonnes = (Colonne*)malloc(nb_colonnes * sizeof(Colonne));

    // Vérifier si l'allocation pour les colonnes a réussi
    if (table->colonnes == NULL) {
        free(table);  // Libérer la mémoire allouée pour la table
        return NULL;
    }

    // Copier les colonnes dans la table
    memcpy(table->colonnes, colonnes, nb_colonnes * sizeof(Colonne));
    table->lignes = NULL;  // Pas encore de lignes
    table->nb_lignes = 0;

    return table;  // Retourner la table créée
}

// Fonction pour créer une nouvelle ligne (tableau de valeurs)
void* creer_ligne(int nb_colonnes) {
    return malloc(nb_colonnes * sizeof(void*)); // Allouer de la mémoire pour une ligne
}

// Fonction pour ajouter une ligne dans la table
void ajouter_ligne(Table* table, void* ligne) {
    if (table == NULL || ligne == NULL) {
        return;  // Si la table ou la ligne est NULL, on ne fait rien
    }

    // Redimensionner le tableau de lignes pour accueillir une nouvelle ligne
    void** new_lignes = realloc(table->lignes, (table->nb_lignes + 1) * sizeof(void*));
    if (new_lignes == NULL) {
        return;  // Si l'allocation échoue, on ne fait rien
    }
    
    table->lignes = new_lignes; // Mettre à jour le tableau de lignes
    table->lignes[table->nb_lignes] = ligne; // Ajouter la nouvelle ligne
    table->nb_lignes++;  // Incrémenter le nombre de lignes
}

// Fonction pour afficher la table (colonnes et lignes)
void afficher_table(Table* table) {
    if (table == NULL) {
        return; // Si la table est NULL, on ne fait rien
    }

    // Affichage des noms de colonnes
    for (int i = 0; i < table->nb_colonnes; i++) {
        printf("%s\t", table->colonnes[i].nom);
    }
    printf("\n");

    // Affichage des valeurs dans chaque ligne
    for (int i = 0; i < table->nb_lignes; i++) {
        void** ligne = (void**)table->lignes[i];  // Récupérer la ligne

        for (int j = 0; j < table->nb_colonnes; j++) {
            if (table->colonnes[j].type == TYPE_COLONNE_INT) {
                printf("%d\t", *((int*)ligne[j]));  // Afficher la valeur si c'est un entier
            } else if (table->colonnes[j].type == TYPE_COLONNE_TEXTE) {
                printf("%s\t", (char*)ligne[j]);  // Afficher la valeur si c'est du texte
            }
        }
        printf("\n");
    }
}

// Fonction pour libérer la mémoire d'une ligne
void liberer_ligne(void* ligne, int nb_colonnes) {
    if (ligne == NULL) {
        return; // Si la ligne est NULL, on ne fait rien
    }

    void** valeurs = (void**)ligne;

    // Libérer la mémoire de chaque valeur dans la ligne
    for (int i = 0; i < nb_colonnes; i++) {
        free(valeurs[i]);
    }

    free(ligne);  // Libérer la mémoire pour la ligne elle-même
}

// Fonction pour libérer la mémoire d'une table
void liberer_table(Table* table) {
    if (table == NULL) {
        return; // Si la table est NULL, on ne fait rien
    }

    // Libérer chaque ligne
    for (int i = 0; i < table->nb_lignes; i++) {
        liberer_ligne(table->lignes[i], table->nb_colonnes);
    }

    // Libérer les colonnes et la table
    free(table->lignes);
    free(table->colonnes);
    free(table);
}
