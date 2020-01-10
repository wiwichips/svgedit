CC = gcc
CFLAGS = -Wall -std=c11 -g -Iinclude
SRC = src/
BIN = bin/
INC = include

liblist: $(SRC)LinkedListAPI.c
	$(CC) $(SRC)LinkedListAPI.c $(CFLAGS) -shared -o bin/liblist.so

clean:
	rm bin/*.o
	rm bin/*.so