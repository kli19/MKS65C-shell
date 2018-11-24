all: shell.o parse.o
	gcc shell.o parse.o

shell.o: shell.c shell.h
	gcc -c shell.c

parse.o: parse.c parse.h
	gcc -c parse.c

clean:
	rm *.o
	rm a.out

run: all
	./a.out
	make clean
