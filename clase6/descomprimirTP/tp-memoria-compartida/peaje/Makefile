#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean peaje autos

peaje : peaje.c archivos.h semaforos.h clave.h def.h funciones.h memoria.h
	$(CC) $(FLAGS) -o peaje peaje.c archivos.c semaforos.c clave.c funciones.c memoria.c

autos : autos.c archivos.h semaforos.h clave.h def.h funciones.h memoria.h
	$(CC) $(FLAGS) -o autos autos.c archivos.c semaforos.c clave.c funciones.c memoria.c

clean: 	
	rm -rf *.o peaje autos *.dat