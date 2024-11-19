#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

// Constantes pour les limites de taille
#define MAX_COLONNES 100
#define MAX_LONGUEUR_NOM 50
#define MAX_LONGUEUR_VALEUR 255

// Types possibles pour les colonnes
typedef enum {
    TYPE_COLONNE_INT,
    TYPE_COLONNE_TEXTE
} TypeColonne;

// Structure pour une colonne
typedef struct {
    char nom[MAX_LONGUEUR_NOM];
    TypeColonne type;
} Colonne;

// Structure pour une table
typedef struct {
    char nom[MAX_LONGUEUR_NOM];
    int nb_colonnes;
    Colonne* colonnes;
    void** lignes;
    int nb_lignes;
    Node* arbre;
} Table;

// Prototypes de fonctions pour manipuler la table
Table* creer_table(const char* nom, int nb_colonnes, Colonne* colonnes);
void ajouter_ligne(Table* table, void* ligne);
void afficher_table(Table* table);
void liberer_table(Table* table);
void* creer_ligne(int nb_colonnes);
void liberer_ligne(void* ligne, int nb_colonnes);
void insert_arbre(Table* table, int data, void* line);
void* search_arbre(Table* table, int data);
void sauvegarder(Table* table, const char* fichier);
void charger(Table* table, const char* fichier);

#endif