# comentamos

CC = gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -pthread -O3 -I./

all: clean pTablero pJugador

pTablero : mainTablero.c global.h archivos.h clave.h semaforo.h funciones.h memoria.h threads.h colas.h
	$(CC) $(FLAGS) -o pTablero mainTablero.c global.c archivos.c clave.c semaforo.c funciones.c memoria.c threads.c colas.c

pJugador : mainJugador.c global.h archivos.h clave.h semaforo.h funciones.h memoria.h threads.h colas.h
	$(CC) $(FLAGS) -o pJugador mainJugador.c global.c archivos.c clave.c semaforo.c funciones.c memoria.c threads.c colas.c




clean:
	rm -f *o pTablero pJugador
	rm -f flag.txt
	
