# Définir le compilateur et les options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Définir les fichiers sources, objets et l'exécutable cible
SOURCES = main.c repl.c btree.c table.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = db

# Cible par défaut pour construire l'exécutable
all: $(TARGET)

# Règle pour lier les objets et créer l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Règle générique pour compiler les fichiers source en objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJECTS) $(TARGET)

# Règle pour exécuter le programme avec Valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

.PHONY: all clean valgrind
