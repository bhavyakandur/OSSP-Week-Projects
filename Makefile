CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

TARGET = bin/shellforge

SRC = src/main.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
