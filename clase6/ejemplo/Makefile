#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean main1 main2

main1 : main1.c archivos.h semaforos.h clave.h def.h funciones.h memoria.h
	$(CC) $(FLAGS) -o main1 main1.c archivos.c semaforos.c clave.c funciones.c memoria.c

main2 : main2.c archivos.h semaforos.h clave.h def.h funciones.h memoria.h
	$(CC) $(FLAGS) -o main2 main2.c archivos.c semaforos.c clave.c funciones.c memoria.c

clean: 	
	rm -rf *.o main1 main2 *.dat