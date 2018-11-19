all: shell.o
	gcc shell.o 

shell.o: shell.c shell.h
	gcc -c shell.c

clear:
	rm *.o

run:
	./a.out
