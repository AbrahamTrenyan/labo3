#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean pienso

pienso : main.c def.h funciones.h global.h thread.h
	$(CC) $(FLAGS) -o pienso main.c funciones.c global.c thread.c

clean: 	
	rm -rf *.o pienso *.dat

