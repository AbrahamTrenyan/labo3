#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean derivador sistema

derivador : derivador.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o derivador derivador.c archivos.c semaforos.c clave.c global.c funciones.c

sistema : sistema.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o sistema sistema.c archivos.c semaforos.c clave.c global.c funciones.c

clean: 
	rm -rf *.o derivador sistema *.dat