CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread
all = clean main

main : main.c funciones.h def.h global.h
	$(CC) $(FLAGS) -o main main.c funciones.c global.c

clean: 
	rm -rf *.o main
