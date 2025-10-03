#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean cola1 cola2

cola1 : cola1.c archivos.h semaforos.h clave.h def.h funciones.h memoria.h mensajes.h 
	$(CC) $(FLAGS) -o cola1 cola1.c archivos.c semaforos.c clave.c funciones.c memoria.c mensajes.c

cola2 : cola2.c archivos.h semaforos.h clave.h def.h funciones.h memoria.h mensajes.h 
	$(CC) $(FLAGS) -o cola2 cola2.c archivos.c semaforos.c clave.c funciones.c memoria.c mensajes.c

clean: 	
	rm -rf *.o cola1 cola2 *.dat