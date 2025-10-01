#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean pienso jugador

pienso : pienso.c archivos.h semaforos.h clave.h def.h funciones.h memoria.h
	$(CC) $(FLAGS) -o pienso pienso.c archivos.c semaforos.c clave.c funciones.c memoria.c

jugador : jugador.c archivos.h semaforos.h clave.h def.h funciones.h memoria.h
	$(CC) $(FLAGS) -o jugador jugador.c archivos.c semaforos.c clave.c funciones.c memoria.c

clean: 	
	rm -rf *.o pienso jugador *.dat