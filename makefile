all:
	gcc -c main.c -Wall -Wextra
	gcc -o lab0 main.o -lm
