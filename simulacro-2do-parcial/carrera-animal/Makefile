#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean pista animales 
animales : animales.c def.h funciones.h global.h mensajes.h memoria.h archivos.h thread.h	
	$(CC) $(FLAGS) -o animales animales.c funciones.c global.c mensajes.c memoria.c clave.c thread.c archivos.c
pista : pista.c def.h funciones.h global.h mensajes.h memoria.h archivos.h thread.h
	$(CC) $(FLAGS) -o pista pista.c funciones.c global.c mensajes.c memoria.c clave.c thread.c archivos.c

clean: 	
	rm -rf *.o pista animales *.dat 
