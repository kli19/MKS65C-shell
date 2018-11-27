all: shell.o parse.o redirect.o
	gcc shell.o parse.o redirect.o

shell.o: shell.c shell.h
	gcc -c shell.c

parse.o: parse.c parse.h
	gcc -c parse.c

redirect.o: redirect.c redirect.h
	gcc -c redirect.c

clean:
	rm *.o
	rm a.out

run: all
	./a.out
	make clean
