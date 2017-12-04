all: shell.o
	gcc shell.o -o shell

shell.o: shell.c shell.h
	gcc -c shell.c

clean:
	rm -f *o
	rm -f *~
	rm shell

run: all
	./shell
