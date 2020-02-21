CC=gcc
CFLAGS=-ansi -Wall -pedantic

a4: hash.o a4.o a4.h
	$(CC) hash.o a4.o -o $@

a4.o: a4.c a4.h
	$(CC) $(CFLAGS) -c a4.c -o $@

hash.o: hash.c a4.h 
	$(CC) $(CFLAGS) -c hash.c -o $@
