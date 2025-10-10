# comentamos

CC = gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -pthread -O3 -I./

all: clean  pCajero pBanco

pCajero : mainCajero.c global.h archivos.h clave.h semaforo.h funciones.h memoria.h colas.h
	$(CC) $(FLAGS) -o pCajero mainCajero.c global.c archivos.c clave.c semaforo.c funciones.c memoria.c colas.c

pBanco : mainBanco.c global.h archivos.h clave.h semaforo.h funciones.h memoria.h colas.h
	$(CC) $(FLAGS) -o pBanco mainBanco.c global.c archivos.c clave.c semaforo.c funciones.c memoria.c colas.c



clean:
	rm -f *o  pCajero pBanco
	
