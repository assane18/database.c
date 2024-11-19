#ifndef REPL_H
#define REPL_H

#include <stdbool.h>
#include <sys/types.h> // Ajouté pour ssize_t
#include "table.h"

// Types de retour pour les commandes utilisateurs
typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
  PREPARE_SUCCESS,
  PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

// Types d'instructions possibles
typedef enum {
  STATEMENT_INSERT,
  STATEMENT_SELECT
} StatementType;

// Structure pour une instruction
typedef struct {
  StatementType type;
  char* data;
} Statement;

// Structure pour le tampon d'entrée
typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length; // Utilisation de ssize_t pour la longueur de l'entrée
} InputBuffer;

// Prototypes de fonctions
InputBuffer* new_input_buffer();
void print_prompt();
void read_input(InputBuffer* input_buffer);
void close_input_buffer(InputBuffer* input_buffer);
MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table);
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);
void execute_statement(Statement* statement, Table* table);
void repl(Table* table);

#endif
