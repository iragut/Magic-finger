# Declaratiile de variabile
CC = gcc
CFLAGS = -g -Wall -lm -std=c99
 
build:  main.c
	$(CC) -o magic main.c $(CFLAGS)

run:
	valgrind ./magic
.PHONY : clean
clean :
	rm -f tema1
	rm -f *.out
	rm my_diff
