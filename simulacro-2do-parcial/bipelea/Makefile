#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean ring equipos
equipos : equipos.c def.h funciones.h global.h mensajes.h memoria.h archivos.h thread.h	
	$(CC) $(FLAGS) -o equipos equipos.c funciones.c global.c mensajes.c memoria.c clave.c thread.c archivos.c
ring : ring.c def.h funciones.h global.h mensajes.h memoria.h archivos.h thread.h
	$(CC) $(FLAGS) -o ring ring.c funciones.c global.c mensajes.c memoria.c clave.c thread.c archivos.c

clean: 	
	rm -rf *.o ring equipos *.dat 
