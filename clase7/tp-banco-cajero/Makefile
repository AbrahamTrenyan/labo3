#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean banco cajero

banco : banco.c archivos.h semaforos.h clave.h def.h funciones.h memoria.h mensajes.h 
	$(CC) $(FLAGS) -o banco banco.c archivos.c semaforos.c clave.c funciones.c memoria.c mensajes.c

cajero : cajero.c archivos.h semaforos.h clave.h def.h funciones.h memoria.h mensajes.h 
	$(CC) $(FLAGS) -o cajero cajero.c archivos.c semaforos.c clave.c funciones.c memoria.c mensajes.c

clean: 	
	rm -rf *.o banco cajero *.dat
