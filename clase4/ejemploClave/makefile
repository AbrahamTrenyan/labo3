CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread
all: clean main

main : main.c clave.h 
	$(CC) $(FLAGS) -o main main.c  clave.c

clean: 
	rm -rf *.o main

