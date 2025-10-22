#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean revolver jugador
jugador : jugadores.c def.h funciones.h global.h mensajes.h memoria.h
	$(CC) $(FLAGS) -o jugador jugadores.c funciones.c global.c mensajes.c memoria.c clave.c thread.c
revolver : revolver.c def.h funciones.h global.h mensajes.h memoria.h
	$(CC) $(FLAGS) -o revolver revolver.c funciones.c global.c mensajes.c memoria.c clave.c

clean: 	
	rm -rf *.o revolver jugador *.dat 
