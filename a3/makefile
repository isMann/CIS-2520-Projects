CC=gcc
CFLAGS=-ansi -Wall -pedantic -g

a3: binary.h common.h name.h title.h principals.h binary.o name.o title.o main.o principals.o common.o
	$(CC) main.o binary.o name.o title.o principals.o common.o -o $@

main.o: main.c common.h 
	$(CC) $(CFLAGS) -c main.c -o $@

binary.o: binary.c common.h common.c
	$(CC) $(CFLAGS) -c binary.c -o $@

name.o: binary.h common.h name.c common.c
	$(CC) $(CFLAGS) -c name.c -o $@

title.o: binary.h common.h title.c common.c
	$(CC) $(CFLAGS) -c title.c -o $@

principals.o: binary.h common.h principals.c common.c
	$(CC) $(CFLAGS) -c principals.c -o $@

common.o: common.h common.c
	$(CC) $(CFLAGS) -c common.c -o $@
