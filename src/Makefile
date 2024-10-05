CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
SOURCES = main.c repl.c btree.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = db

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
