/*
 * Name: Michael Mann
 * ID: 1037704
 * Email mmann10@uoguelph.ca
 */
#include "ds_array.h"
#include "ds_memory.h"
#include <stdlib.h>

long elements;
/*incomplete don't know how big to malloc array*/
int ds_create_array(){
	if(ds_init("array.bin")){
		return 1;
	}

	if(ds_malloc(sizeof(long)) == -1){
		return 1;
	}
	elements = 0;
	if((ds_malloc(sizeof(int) * MAX_ELEMENTS)) == -1){
		return 1;
	}
	return !ds_finish();
}

int ds_init_array(){
	long other;
	if(ds_init("array.bin")){
		return 1;
	}
	other = 0;
	/*read at index of 0 and make temp that address so elements can be that address*/
	if(ds_read(&other, 0, sizeof(long)) == NULL){
		return 1;
	}
	elements = other;

	return 0;
}

int ds_replace(int value, long index){
	if(index >= elements){
		return 1;
	}
	else{
		/*write to the address of the index by adding elements and the num of items*/
		if(ds_write(sizeof(long) + sizeof(int) * index, &value, sizeof(int)) == -1){
			return 1;
		}
		else{
			return 0;
		}
	}
}

int ds_insert(int value, long index){
	int old, new;
	new = value;
	if(index == elements){
		/*write to the end*/
		if(ds_write(sizeof(long) + sizeof(int) * index, &new, sizeof(int)) == -1){
			return 1;
		}
	}
	else if((index > elements) || index < 0){
		return 1;
	}
	else{
		for(; index < elements; index++){
			/*read the current at the index*/
			ds_read(&old, sizeof(long) + sizeof(int) * index, sizeof(int));
			/*write to that address*/
			ds_write(sizeof(long) + sizeof(int) * index, &new, sizeof(int));
			/*make the next value be the one read*/
			new = old;
		}
		if(ds_write(sizeof(long) + sizeof(int) * index, &new, sizeof(int)) == -1){
			return 1;
		}
	}
	elements++;
	return 0;
}

int ds_delete(long index){
	int temp;
	if(index < 0 || index >= elements){
		return 1;
	}
	else if(index == elements - 1){
		/*last element just delete it*/
		if(ds_write(sizeof(long) + sizeof(int) * index, &temp, sizeof(int)) == -1){
			return 1;
		}
	}
	else{
		for(; index < elements - 1; index++){
			/*take the next index print it to this one*/
			if(ds_read(&temp, sizeof(long) + sizeof(int) * (index + 1), sizeof(int)) == NULL){
				return 1;
			}
			if(ds_write(sizeof(long) + sizeof(int) * index, &temp, sizeof(int)) == -1){
				return 1;
			}
		}

		if(ds_write(sizeof(long) + sizeof(int) * index, &temp, sizeof(int)) == -1){
			return 1;
		}
	}
	elements--;
	return 0;
}

int ds_swap(long index1, long index2){
	int num1, num2;
	if(ds_read(&num1, sizeof(long) + sizeof(int) * index1, sizeof(int)) == NULL ||
	ds_read(&num2, sizeof(long) + sizeof(int) * index2, sizeof(int)) == NULL){
		return 1;
	}
	if(ds_write(sizeof(long) + sizeof(int) * index2, &num1, sizeof(int)) == -1 ||
	ds_write(sizeof(long) + sizeof(int) * index1, &num2, sizeof(int)) == -1){
		return 1;
	}

	return 0;
}

long ds_find(int target){
	long i;
	int temp;
	for(i = 0; i < elements; i++){
		if(ds_read(&temp, sizeof(long) + sizeof(int) * i, sizeof(int)) == NULL){
			return 1;
		}
		if(temp == target){
				return i;
		}
	}
	return -1;
}

int ds_read_elements(char *filename){
	FILE *fp;
	int num;
	fp = fopen(filename, "r");

	while(fscanf(fp, "%d", &num) != EOF){
		if(ds_insert(num, elements)){
			return 1;
		}
	}
	return 0;
}

int ds_finish_array(){
	long temp;
	temp = elements;
	if(ds_write(0, &temp, sizeof(long)) == -1){
		return 1;
	}
	return !ds_finish();
}
