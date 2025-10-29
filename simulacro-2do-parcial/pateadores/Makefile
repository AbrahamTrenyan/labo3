#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean arquero pateadores 
arquero : arquero.c def.h funciones.h global.h mensajes.h memoria.h archivos.h thread.h	
	$(CC) $(FLAGS) -o arquero arquero.c funciones.c global.c mensajes.c memoria.c clave.c thread.c archivos.c
pateadores : pateadores.c def.h funciones.h global.h mensajes.h memoria.h archivos.h thread.h
	$(CC) $(FLAGS) -o pateadores pateadores.c funciones.c global.c mensajes.c memoria.c clave.c thread.c archivos.c

clean: 	
	rm -rf *.o arquero pateadores *.dat 
