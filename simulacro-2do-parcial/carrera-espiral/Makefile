#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean tablero jugadores 
tablero : tablero.c def.h funciones.h global.h mensajes.h memoria.h archivos.h thread.h	
	$(CC) $(FLAGS) -o tablero tablero.c funciones.c global.c mensajes.c memoria.c clave.c thread.c archivos.c
jugadores : jugadores.c def.h funciones.h global.h mensajes.h memoria.h archivos.h thread.h
	$(CC) $(FLAGS) -o jugadores jugadores.c funciones.c global.c mensajes.c memoria.c clave.c thread.c archivos.c

clean: 	
	rm -rf *.o tablero jugadores *.dat 
