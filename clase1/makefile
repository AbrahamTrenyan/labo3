CC = gcc-4.1

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

HEADERS = -I./

all = clean prog

prog:
	$(CC) -o main main.c funciones.c  $(CFLAGS) $(HEADERS)

clean: rm -rf *o main