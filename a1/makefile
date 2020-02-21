CFLAGS=-ansi -Wall -g -pedantic
CC=gcc
INCL=ds_memory.h

all: array list 

clean: rm *.o 

array: ds_array.o ds_memory.o 
	$(CC) ds_array.o ds_memory.o -o $@

list: ds_list.o ds_memory.o 
	$(CC) ds_list.o ds_memory.o -o $@

ds_memory.o: ds_memory.c
	$(CC) $(CFLAGS) -c ds_memory.c -o $@

ds_array.o: ds_array.c
	$(CC) $(CFLAGS) -c ds_array.c -o $@

arraytest.o: arraytest.c
	$(CC) $(CFLAGS) -c arraytest.c -o $@

ds_list.o: ds_list.c
	$(CC) $(CFLAGS) -c ds_list.c -o $@


