CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -O2 -Iinclude

SRC = src/main.c src/cli.c src/terminal.c src/editor.c src/errors.c
OBJ = $(SRC:.c=.o)

TARGET = cvim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
