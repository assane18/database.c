# Utilisation de GCC avec des options pour afficher des avertissements supplémentaires
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Les fichiers sources et les cibles
SOURCES = main.c repl.c btree.c table.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = db

# Cible principale qui construit le programme
all: $(TARGET)

# Règle pour lier les fichiers objets et créer l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Règle pour compiler les fichiers .c en fichiers .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJECTS) $(TARGET)

# Tester le programme avec Valgrind pour détecter les fuites de mémoire
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

.PHONY: all clean valgrind