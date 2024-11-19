#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ajoute une ligne à l'arbre pour une table donnée
void insert_arbre(Table* table, int data, void* line) {
    if (table->arbre == NULL) {
        table->arbre = create_node(data);
        table->arbre->line = line;
    } else {
        insert(table->arbre, data, line);
    }
}

// Effectue une recherche dans l'arbre binaire
void* search_arbre(Table* table, int data) {
    if (table->arbre == NULL) {
        return NULL;
    }
    return search(table->arbre, data);
}

// Crée une nouvelle table en mémoire
Table* creer_table(const char* nom, int nb_colonnes, Colonne* colonnes) {
    if (nb_colonnes <= 0 || colonnes == NULL) {
        return NULL; // Vérification des paramètres
    }

    Table* table = (Table*)malloc(sizeof(Table));
    if (table == NULL) {
        return NULL; // Échec allocation mémoire
    }

    strncpy(table->nom, nom, MAX_LONGUEUR_NOM);
    table->nom[MAX_LONGUEUR_NOM - 1] = '\0'; // Terminaison du nom

    table->nb_colonnes = nb_colonnes;
    table->colonnes = (Colonne*)malloc(nb_colonnes * sizeof(Colonne));
    
    if (table->colonnes == NULL) {
        free(table);
        return NULL;
    }

    memcpy(table->colonnes, colonnes, nb_colonnes * sizeof(Colonne));
    table->lignes = NULL;
    table->nb_lignes = 0;
    table->arbre = NULL; // Initialisation de l'arbre

    return table; // Retourne la nouvelle table
}

// Crée un tableau pour stocker les valeurs d'une ligne
void* creer_ligne(int nb_colonnes) {
    return malloc(nb_colonnes * sizeof(void*));
}

// Ajoute une nouvelle ligne à la table
void ajouter_ligne(Table* table, void* ligne) {
    if (table == NULL || ligne == NULL) {
        return;  // Vérification des pointeurs
    }

    void** new_lignes = realloc(table->lignes, (table->nb_lignes + 1) * sizeof(void*));
    if (new_lignes == NULL) {
        return;  // Vérification de l'allocation
    }

    table->lignes = new_lignes;
    table->lignes[table->nb_lignes] = ligne;
    table->nb_lignes++;
}

// Affiche toute la table
void afficher_table(Table* table) {
    if (table == NULL) {
        return;
    }

    for (int i = 0; i < table->nb_colonnes; i++) {
        printf("%s\t", table->colonnes[i].nom);
    }
    printf("\n");

    for (int i = 0; i < table->nb_lignes; i++) {
        void** ligne = (void**)table->lignes[i];
        for (int j = 0; j < table->nb_colonnes; j++) {
            if (table->colonnes[j].type == TYPE_COLONNE_INT) {
                printf("%d\t", *((int*)ligne[j]));
            } else if (table->colonnes[j].type == TYPE_COLONNE_TEXTE) {
                printf("%s\t", (char*)ligne[j]);
            }
        }
        printf("\n");
    }
}

// Libère la mémoire d'une seule ligne
void liberer_ligne(void* ligne, int nb_colonnes) {
    if (ligne == NULL) {
        return;
    }

    void** valeurs = (void**)ligne;
    for (int i = 0; i < nb_colonnes; i++) {
        free(valeurs[i]);
    }
    free(ligne);
}

// Libère toutes les ressources utilisées par une table
void liberer_table(Table* table) {
    if (table == NULL) {
        return;
    }

    for (int i = 0; i < table->nb_lignes; i++) {
        liberer_ligne(table->lignes[i], table->nb_colonnes);
    }

    free(table->lignes);
    free(table->colonnes);
    free(table);
}

// Sauvegarde les données de la table dans un fichier
void sauvegarder(Table* table, const char* fichier) {
    FILE* file = fopen(fichier, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    for (int i = 0; i < table->nb_lignes; i++) {
        void** ligne = (void**)table->lignes[i];
        fprintf(file, "%d %s %s %d\n", *((int*)ligne[0]), (char*)ligne[1], (char*)ligne[2], *((int*)ligne[3]));
    }
    fclose(file);
}

// Charge les données d'un fichier dans une table
void charger(Table* table, const char* fichier) {
    FILE* file = fopen(fichier, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    char ligne[256];
    while (fgets(ligne, 256, file) != NULL) {
        int id;
        char nom[50], prenom[50];
        int age;
        sscanf(ligne, "%d %49s %49s %d", &id, nom, prenom, &age);
        void** ligne_data = creer_ligne(table->nb_colonnes);
        ligne_data[0] = malloc(sizeof(int));
        *((int*)ligne_data[0]) = id;
        ligne_data[1] = malloc(strlen(nom) + 1);
        strcpy(ligne_data[1], nom);
        ligne_data[2] = malloc(strlen(prenom) + 1);
        strcpy(ligne_data[2], prenom);
        ligne_data[3] = malloc(sizeof(int));
        *((int*)ligne_data[3]) = age;
        ajouter_ligne(table, ligne_data);
        insert_arbre(table, id, ligne_data);
    }
    fclose(file);
}