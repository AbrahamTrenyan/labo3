#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean panel equipo

panel : panel.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o panel panel.c archivos.c semaforos.c clave.c global.c funciones.c

equipo : equipo.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o equipo equipo.c archivos.c semaforos.c clave.c global.c funciones.c

clean: 
	rm -rf *.o panel equipo *.dat