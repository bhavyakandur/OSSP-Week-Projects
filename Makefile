CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

TARGET = bin/shellforge

SRC = src/main.c src/execute.c src/builtin.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
