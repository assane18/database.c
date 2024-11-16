#ifndef REPL_H
#define REPL_H

#include <stdbool.h>  // Pour les types booléens (true/false)
#include "table.h"    // Inclure le fichier table.h pour manipuler les tables

// Enumération pour les résultats des commandes métas (comme .exit)
typedef enum {
  META_COMMAND_SUCCESS,  // La commande a réussi
  META_COMMAND_UNRECOGNIZED_COMMAND  // La commande n'est pas reconnue
} MetaCommandResult;

// Enumération pour les résultats lors de la préparation d'une instruction
typedef enum { 
  PREPARE_SUCCESS,           // L'instruction a été préparée avec succès
  PREPARE_UNRECOGNIZED_STATEMENT  // L'instruction est non reconnue
} PrepareResult;

// Enumération pour différents types d'instructions (INSERT ou SELECT)
typedef enum { 
  STATEMENT_INSERT,   // Instruction d'insertion
  STATEMENT_SELECT    // Instruction de sélection
} StatementType;

// Structure représentant une instruction, qui a un type
typedef struct {
  StatementType type;  // Type de l'instruction (INSERT ou SELECT)
} Statement;

// Structure représentant le tampon d'entrée de l'utilisateur
typedef struct {
  char* buffer;         // Le tampon contenant l'entrée de l'utilisateur
  size_t buffer_length; // La longueur actuelle du tampon
  ssize_t input_length; // La longueur de l'entrée de l'utilisateur (sans le \0)
} InputBuffer;

// Fonction pour créer un nouveau tampon d'entrée
InputBuffer* new_input_buffer();

// Fonction pour afficher l'invite de commande (par exemple "db > ")
void print_prompt();

// Fonction pour lire l'entrée de l'utilisateur
void read_input(InputBuffer* input_buffer);

// Fonction pour fermer le tampon d'entrée et libérer la mémoire
void close_input_buffer(InputBuffer* input_buffer);

// Fonction pour gérer les commandes métas (comme .exit)
MetaCommandResult do_meta_command(InputBuffer* input_buffer);

// Fonction pour préparer une instruction à exécuter
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);

// Fonction pour exécuter une instruction préparée
void execute_statement(Statement* statement);

// Fonction REPL (Read-Eval-Print Loop), qui boucle pour recevoir les commandes de l'utilisateur
void repl(Table* table); // Modifie cette ligne si tu veux passer une table à repl

#endif // REPL_H
