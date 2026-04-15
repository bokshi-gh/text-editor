CC      = gcc
CFLAGS = -std=c99 -Wall -Wextra -O2 -Iinclude

SRC = \
			src/main.c

OBJ = $(SRC:.c=.o)

TARGET = cvim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
