#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Nécessaire pour strdup
#include <sys/types.h>
#include "table.h" // Assurez-vous que ce fichier est inclus pour le type Table

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum { 
    PREPARE_SUCCESS, 
    PREPARE_UNRECOGNIZED_STATEMENT 
} PrepareResult;

typedef enum { 
    STATEMENT_INSERT, 
    STATEMENT_SELECT 
} StatementType;

typedef struct {
    StatementType type;
    char* data; // Utilisation de char* pour les données
} Statement;

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

// Fonction pour créer un nouveau tampon d'entrée
InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer_length = 256; // Longueur initiale du tampon
    input_buffer->buffer = (char*)malloc(input_buffer->buffer_length);
    input_buffer->input_length = 0;
    return input_buffer;
}

// Fonction pour afficher l'invite de commande
void print_prompt() {
    printf("db > ");
}

// Fonction pour lire l'entrée de l'utilisateur
void read_input(InputBuffer* input_buffer) {
    fgets(input_buffer->buffer, input_buffer->buffer_length, stdin);

    // Vérification si la lecture a échoué
    if (feof(stdin)) {
        printf("Erreur lors de la lecture de l'entrée\n");
        exit(EXIT_FAILURE);
    }

    // Supprimer le caractère de nouvelle ligne
    input_buffer->input_length = strlen(input_buffer->buffer);
    if (input_buffer->buffer[input_buffer->input_length - 1] == '\n') {
        input_buffer->buffer[input_buffer->input_length - 1] = '\0'; // Remplace le \n par \0
        input_buffer->input_length--; // Met à jour la longueur
    }
}

// Fonction pour fermer le tampon d'entrée
void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

// Fonction pour traiter les commandes métas
MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

// Fonction pour préparer les instructions
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        // Stocker les données après "insert "
        // Utilisation de malloc et strcpy au lieu de strdup
        size_t len = strlen(input_buffer->buffer + 7);
        statement->data = malloc(len + 1); // +1 pour le caractère nul
        strcpy(statement->data, input_buffer->buffer + 7); // Copie les données
        return PREPARE_SUCCESS;
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}

// Fonction pour exécuter les instructions
void execute_statement(Statement* statement, Table* table) {
    switch (statement->type) {
        case (STATEMENT_INSERT): {
            // Supposons que les données soient au format "ID Nom Prenom Age"
            int id;
            char nom[50], prenom[50];
            int age;

            // Récupération des données depuis statement->data
            sscanf(statement->data, "%d %49s %49s %d", &id, nom, prenom, &age);
            void** ligne = creer_ligne(table->nb_colonnes); // Créer une nouvelle ligne

            ligne[0] = malloc(sizeof(int)); // Allouer de la mémoire pour l'ID
            *((int*)ligne[0]) = id; // Assigner l'ID

            ligne[1] = malloc(strlen(nom) + 1); // Allouer mémoire pour le nom
            strcpy(ligne[1], nom); // Copier le nom

            ligne[2] = malloc(strlen(prenom) + 1); // Allouer mémoire pour le prénom
            strcpy(ligne[2], prenom); // Copier le prénom

            ligne[3] = malloc(sizeof(int)); // Allouer de la mémoire pour l'âge
            *((int*)ligne[3]) = age; // Assigner l'âge
            
            ajouter_ligne(table, ligne); // Ajouter la ligne à la table
            printf("Insertion réussie : %d %s %s %d\n", id, nom, prenom, age);
            break;
        }
        case (STATEMENT_SELECT):
            afficher_table(table); // Afficher la table
            break;
    }
}

// Boucle REPL principale
void repl(Table* table) {
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);
        
        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer)) {
                case META_COMMAND_SUCCESS:
                    continue; // Continue si la commande a réussi
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    printf("Commande méta non reconnue : %s\n", input_buffer->buffer);
                    continue; // Continue en cas d'erreur
            }
        }

        Statement statement;
        PrepareResult prepare_result = prepare_statement(input_buffer, &statement);
        
        switch (prepare_result) {
            case PREPARE_SUCCESS:
                execute_statement(&statement, table); // Utilise le paramètre table ici
                break;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                printf("Instruction non reconnue : %s\n", input_buffer->buffer);
                break;
        }

        // Libérer la mémoire allouée pour statement->data après utilisation
        if (statement.data != NULL) {
            free(statement.data); // Libère la mémoire de statement->data
            statement.data = NULL; // Réinitialiser le pointeur pour éviter un double free
        }
    }
    close_input_buffer(input_buffer);
}
