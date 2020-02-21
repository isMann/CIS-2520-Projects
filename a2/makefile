CC=gcc
CFLAGS=-ansi -Wall -g -pedantic

all: exe

clean: rm *.o exe

exe: main.o text.o
	$(CC) main.o text.o -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o $@

text.o: text.c
	$(CC) $(CFLAGS) -c text.c -o $@
