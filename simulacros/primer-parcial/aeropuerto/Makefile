#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean panel avion

panel : panel.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o panel panel.c archivos.c semaforos.c clave.c funciones.c global.c

avion : avion.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o avion avion.c archivos.c semaforos.c clave.c funciones.c global.c

clean: 
	rm -rf *.o panel avion *.dat