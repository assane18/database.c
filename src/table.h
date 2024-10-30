#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Définir des constantes pour les longueurs maximales
#define MAX_COLONNES 100
#define MAX_LONGUEUR_NOM 50
#define MAX_LONGUEUR_VALEUR 255

// Enumération pour définir les types de colonnes possibles
typedef enum {
    TYPE_COLONNE_INT,  // Colonne de type entier
    TYPE_COLONNE_TEXTE // Colonne de type texte
} TypeColonne;

// Structure pour représenter une colonne
typedef struct {
    char nom[MAX_LONGUEUR_NOM];  // Nom de la colonne
    TypeColonne type;            // Type de la colonne (int ou texte)
} Colonne;

// Structure pour représenter une table
typedef struct {
    char nom[MAX_LONGUEUR_NOM];  // Nom de la table
    int nb_colonnes;             // Nombre de colonnes dans la table
    Colonne* colonnes;           // Tableau de colonnes
    void** lignes;               // Tableau de lignes, chaque ligne est un tableau de valeurs
    int nb_lignes;               // Nombre de lignes dans la table
} Table;

// Fonctions pour créer et manipuler une table
Table* creer_table(const char* nom, int nb_colonnes, Colonne* colonnes);
void ajouter_ligne(Table* table, void* ligne);
void afficher_table(Table* table);
void liberer_table(Table* table);

// Fonctions pour gérer la création et la suppression des lignes
void* creer_ligne(int nb_colonnes);
void liberer_ligne(void* ligne, int nb_colonnes);

#endif
