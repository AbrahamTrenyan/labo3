CC=gcc-4.1

CFLAGS = -Wall -O3 -std=gnu89 -pedantic-errors -pthread
HEADERS = -I./

all: clean main

main: main.c clave.c memoria.c colas.c global.c
	$(CC) -o main main.c colas.c clave.c memoria.c global.c $(CFLAGS) $(HEADERS)

clean:
	rm -rf *.o main
