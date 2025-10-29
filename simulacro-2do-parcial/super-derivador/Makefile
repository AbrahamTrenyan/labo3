#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean derivador cajas
derivador : derivador.c def.h funciones.h global.h mensajes.h memoria.h archivos.h thread.h	
	$(CC) $(FLAGS) -o derivador derivador.c funciones.c global.c mensajes.c memoria.c clave.c thread.c archivos.c semaforos.c
cajas : cajas.c def.h funciones.h global.h mensajes.h memoria.h archivos.h thread.h
	$(CC) $(FLAGS) -o cajas cajas.c funciones.c global.c mensajes.c memoria.c clave.c thread.c archivos.c semaforos.c

clean: 	
	rm -rf *.o derivador cajas *.dat 
