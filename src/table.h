#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Définir des constantes pour les longueurs maximales
#define MAX_COLONNES 100  // Nombre maximum de colonnes dans une table
#define MAX_LONGUEUR_NOM 50  // Longueur maximale pour le nom des colonnes et de la table
#define MAX_LONGUEUR_VALEUR 255  // Longueur maximale pour les valeurs dans les cellules

// Enumération pour définir les types de colonnes possibles
typedef enum {
    TYPE_COLONNE_INT,  // Colonne de type entier
    TYPE_COLONNE_TEXTE // Colonne de type texte
} TypeColonne;

// Structure pour représenter une colonne dans la table
typedef struct {
    char nom[MAX_LONGUEUR_NOM];  // Nom de la colonne (ex: "id", "nom")
    TypeColonne type;            // Type de la colonne (entier ou texte)
} Colonne;

// Structure pour représenter une table
typedef struct {
    char nom[MAX_LONGUEUR_NOM];  // Nom de la table (ex: "utilisateurs", "produits")
    int nb_colonnes;             // Nombre de colonnes dans la table
    Colonne* colonnes;           // Tableau de colonnes, chaque élément est une structure Colonne
    void** lignes;               // Tableau de lignes, chaque ligne est un tableau de valeurs (un tableau de pointeurs)
    int nb_lignes;               // Nombre de lignes dans la table
} Table;

// Fonctions pour créer et manipuler une table

// Créer une table avec un nom, un nombre de colonnes, et un tableau de colonnes
Table* creer_table(const char* nom, int nb_colonnes, Colonne* colonnes);

// Ajouter une ligne dans la table
void ajouter_ligne(Table* table, void* ligne);

// Afficher la table avec ses colonnes et ses lignes
void afficher_table(Table* table);

// Libérer la mémoire allouée pour la table (lignes, colonnes et table elle-même)
void liberer_table(Table* table);

// Fonctions pour gérer la création et la suppression des lignes

// Créer une nouvelle ligne avec un nombre spécifié de colonnes
void* creer_ligne(int nb_colonnes);

// Libérer la mémoire allouée pour une ligne (tableau de valeurs)
void liberer_ligne(void* ligne, int nb_colonnes);

#endif
