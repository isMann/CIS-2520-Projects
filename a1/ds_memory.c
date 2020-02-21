/*
 * Name: Michael Mann
 * ID: 1037704
 * Email mmann10@uoguelph.ca
 */
#include "ds_memory.h"
#include <stdio.h>
#include <stdlib.h>


struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

int ds_create(char *filename, long size){
	int i;
	
	ds_file.fp = fopen(filename, "wb+");
	if (ds_file.fp == NULL){
		return 1;
	}
	
	ds_file.block[0].start = 0;
	ds_file.block[0].length = size;
	ds_file.block[0].alloced = 0;

	for (i = 1; i < MAX_BLOCKS; i++) {
		ds_file.block[i].start = 0;
		ds_file.block[i].length = 0;
		ds_file.block[i].alloced = 0;
	}


	fseek(ds_file.fp, 0, SEEK_SET);

	if(fwrite(ds_file.block, MAX_BLOCKS, sizeof(struct ds_blocks_struct), ds_file.fp) != MAX_BLOCKS * sizeof(struct ds_blocks_struct)){
		return 1;
	}

	for (i = 0; i < size; i++){
		if(!fprintf(ds_file.fp, "%c", 0)){
			return 1;
		}
	}

	return fclose(ds_file.fp);
}

int ds_init(char *filename){

	ds_file.fp = fopen(filename, "rb+");
	if(ds_file.fp == NULL){
		return 1;
	}

	fseek(ds_file.fp, 0, SEEK_SET);
	
	
	fread(ds_file.block, MAX_BLOCKS, sizeof(struct ds_blocks_struct), ds_file.fp); 
	ds_counts.reads = 0;
	ds_counts.writes = 0;
	return 0;
}

long ds_malloc(long amount){
	int i, j, found;
	long init;
	found = 0;
	j = ds_file.block[MAX_BLOCKS].start;
	for(i = 0; i < MAX_BLOCKS; i++){
		if((ds_file.block[i].length >= amount) && !(ds_file.block[i].alloced) && !found){
			j = i;
			init = ds_file.block[i].length;
			ds_file.block[i].length = amount;
			ds_file.block[i].alloced = 1;
			found = 1;
			i = 0;
		}
	       if(!ds_file.block[i].length && found){
		       ds_file.block[i].start = ds_file.block[j].start + amount;
		       ds_file.block[i].length =  init - amount;
		       return ds_file.block[j].start;
	       }
	}
	/*if if the first block is found but not the second return the start else return -1*/
	return -1;
}

void ds_free(long start){
	int i;

	for (i = 0; i < MAX_BLOCKS; i++){
		if(start == ds_file.block[i].start){
			ds_file.block[i].alloced = 0;
		}
	}
}

void *ds_read(void *ptr, long start, long bytes){
	fseek(ds_file.fp, sizeof(struct ds_blocks_struct) * MAX_BLOCKS + start, SEEK_SET);
	if(fread(ptr, 1, bytes, ds_file.fp) == bytes){
		ds_counts.reads++;
		return ptr;
	}
	else{
		return NULL;
	}
}

long ds_write(long start, void *ptr, long bytes){
	fseek(ds_file.fp, sizeof(struct ds_blocks_struct) * MAX_BLOCKS + start, SEEK_SET);
	if(fwrite(ptr, 1, bytes, ds_file.fp) == bytes){
		ds_counts.writes++;
		return start;
	}
	else{
		return -1;
	}
}

int ds_finish(){
	rewind(ds_file.fp);
	fwrite(ds_file.block, sizeof(struct ds_blocks_struct), MAX_BLOCKS, ds_file.fp);

	printf("reads: %d\nwrites: %d\n", ds_counts.reads, ds_counts.writes);
	rewind(ds_file.fp);
	
	/* 
	 * if fclose is successful 0 is returned and EOF otherwise
	 * the ! makes any 0 a 1 and anything else a 0 so this will return
	 * value outlined in the assignment descripiton
	 */
	return !fclose(ds_file.fp);
}

