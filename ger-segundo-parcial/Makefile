CC=gcc-4.1

CFLAGS = -Wall -O3 -std=gnu89 -pedantic-errors -pthread
HEADERS = -I./

all: clean mosquitos espiral

mosquitos: mosquitos.c clave.c memoria.c colas.c threads.c funciones.c
	$(CC) -o mosquitos mosquitos.c colas.c clave.c memoria.c threads.c funciones.c $(CFLAGS) $(HEADERS)

espiral: espiral.c clave.c memoria.c colas.c threads.c funciones.c
	$(CC) -o espiral espiral.c colas.c clave.c memoria.c funciones.c threads.c $(CFLAGS) $(HEADERS)
 

clean:
	rm -rf *.o espiral mosquitos
