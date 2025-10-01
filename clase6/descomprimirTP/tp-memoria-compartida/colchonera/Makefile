#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean colchoneria vendedor

colchoneria : colchoneria.c archivos.h semaforos.h clave.h def.h funciones.h memoria.h
	$(CC) $(FLAGS) -o colchoneria colchoneria.c archivos.c semaforos.c clave.c funciones.c memoria.c

vendedor : vendedor.c archivos.h semaforos.h clave.h def.h funciones.h memoria.h
	$(CC) $(FLAGS) -o vendedor vendedor.c archivos.c semaforos.c clave.c funciones.c memoria.c

clean: 	
	rm -rf *.o colchoneria vendedor *.dat