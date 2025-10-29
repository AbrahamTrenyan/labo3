#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean bingo

bingo : main.c def.h funciones.h global.h thread.h
	$(CC) $(FLAGS) -o bingo main.c funciones.c global.c thread.c

clean: 	
	rm -rf *.o bingo *.dat

