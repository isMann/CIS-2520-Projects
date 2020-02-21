/*
 * Name: Michael Mann
 * ID: 1037704
 * Email mmann10@uoguelph.ca
 */
#include "ds_memory.h"
#include "ds_list.h"

void ds_create_list(){
	long i;
	i = -1;
	ds_init("list.bin");
		
	ds_malloc(sizeof(long));

	ds_write(0, &i, sizeof(long));
	ds_finish();	
}

int ds_init_list(){
	return ds_init("list.bin");
}

int ds_replace(int value, long index){
	long loc, i;
	struct ds_list_item_struct list;
	if(ds_read(&loc, 0, sizeof(long)) == NULL){
		return 1;
	}
	
	if(index < 0){
		return 1;
	}

	if(loc == -1){
		return 1;
	}
	else{ 
		for(i = 1; i <= index; i++){
			if(ds_read(&list, loc, sizeof(struct ds_list_item_struct)) == NULL){
				return 1;
			}
			if(list.next == -1){
				return 1;
			}
			loc = list.next;
		}

		if(ds_read(&list, loc, sizeof(struct ds_list_item_struct)) == NULL){
			return 1;
		}
		list.item = value;
		if(ds_write(loc, &list, sizeof(struct ds_list_item_struct)) == -1){
			return 1;
		}
		else {
			return 0;
		}
	}
}

int ds_delete(long index){
	long loc, i;
	struct ds_list_item_struct list, del;
	if(ds_read(&loc, 0, sizeof(long)) == NULL){
		return 1;
	}

	if(index < 0){
		return 1;
	}
	/*nothing in the list*/
	if(loc == -1){
		return 1;
	}
	/* the first element so read the first one and save the pointer to it,
	 * make the new head the next element free the original head with the
	 * saved pointer */
	else if(index == 0){
		if(ds_read(&list, loc, sizeof(struct ds_list_item_struct)) == NULL){
			return 1;
		}
		i = loc;
		loc = list.next;
		if(ds_write(0, &loc, sizeof(long)) == -1){
			return 1;
		}
		ds_free(i);
	}
	/* not the first one */
	else{
		for (i = 0; i < index; i++){
			if(ds_read(&list, loc, sizeof(struct ds_list_item_struct)) == NULL){
				return 1;
			}
			/* index is not the last element but reached the last element */
			if(list.next == -1){ 
				return 1;
			}
			/* reset for the next loop if it is not the last element */
			if(i != index - 1){
				loc = list.next;
			}
		}
		/* set the new next and save the pointer to the one to delete then write
		 * the new next and delete the one to delete */
		i = list.next;
		if(ds_read(&del, list.next, sizeof(struct ds_list_item_struct)) == NULL){
			return 1;
		}
		list.next = del.next;
		if(ds_write(loc, &list, sizeof(struct ds_list_item_struct)) == -1){
			return 1;
		}
		ds_free(i);
	}
	return 0;
}


int ds_insert(int value, long index){
	struct ds_list_item_struct prev, new;
	long prevloc;
	long i;
	prevloc = 0;
	if(ds_read(&prevloc, 0, sizeof(long)) == NULL){
		return 1;
	}
	/*if the head is -1 and the index is 0*/
	if(prevloc == -1 && !index){
		new.item = value;
		new.next = prevloc;
		prevloc = ds_malloc(sizeof(struct ds_list_item_struct));
		if(ds_write(0, &prevloc, sizeof(long)) == -1){
			return 1;
		}
		if(ds_write(prevloc, &new, sizeof(struct ds_list_item_struct)) == -1){
			return 1;
		}
	}
	/*if the index is less than 0 and therefore invalid*/
	else if(index < 0){
		return 1;
	}
	/*if the index is 0 but there is already something in the list*/
	else if(!index && prevloc != -1){
		new.next = prevloc;
		new.item = value;
		prevloc = ds_malloc(sizeof(struct ds_list_item_struct));
		if(prevloc == -1){
			return 1;
		}
		if(ds_write(prevloc, &new, sizeof(struct ds_list_item_struct)) == -1){
			return 1;
		}
		if(ds_write(0, &prevloc, sizeof(long)) == -1){
			return 1;
		}
	}
	/*it is a not 0 index*/
	else{
		/*there is nothing in the array*/
		if(prevloc == -1){
			return 1;
		}
		/*there is something*/
		for(i = 0; i < index; i++){
			if(ds_read(&prev, prevloc, sizeof(struct ds_list_item_struct)) == NULL){
				return 1;
			}
			/*if the index goes out of bounds but if you're inputting to the end of
			 * the list just make it at the end of the list*/
			if(prev.next == -1 && i != index -1){
				return 1;
			}
			/*set up for the next loop but if it's at the right index
			 * preserve the previous location*/
			if(i != index - 1){
				prevloc = prev.next;
			}
		}
		new.item = value;
		new.next = prev.next;
		prev.next = ds_malloc(sizeof(struct ds_list_item_struct));
		if(ds_write(prev.next, &new, sizeof(struct ds_list_item_struct)) == -1 ||
		ds_write(prevloc, &prev, sizeof(struct ds_list_item_struct)) == -1){
			return 1;
		}
	}
	return 0;
}

int ds_swap(long index1, long index2){
	long loc1, loc2, i, j;
	struct ds_list_item_struct list1, list2;
	int temp;
	if(ds_read(&loc1, 0, sizeof(long)) == NULL){
		return 1;
	}
	loc2 = loc1;
	if(index1 < 0 || index2 < 0){
		return 1;
	}
	if(loc1 == -1){
		return 1;
	}
	else{ 
		for(i = 1; i <= index1; i++){
			if(ds_read(&list1, loc1, sizeof(struct ds_list_item_struct)) == NULL){
				return 1;
			}
			if(list1.next == -1 && i != index1){
				return 1;
			}
			loc1 = list1.next;
		}

		for(j = 1; j <= index2; j++){
			if(ds_read(&list2, loc2, sizeof(struct ds_list_item_struct)) == NULL){
				return 1;
			}
			if(list2.next == -1 && i != index2){
				return 1;
			}
			loc2 = list2.next;
		}
		if(ds_read(&list1, loc1, sizeof(struct ds_list_item_struct)) == NULL ||
		ds_read(&list2, loc2, sizeof(struct ds_list_item_struct)) == NULL){
			return 1;
		}
		temp = list1.item;
		list1.item = list2.item;
		list2.item = temp;
		if(ds_write(loc1, &list1, sizeof(struct ds_list_item_struct)) == -1 ||
		ds_write(loc2, &list2, sizeof(struct ds_list_item_struct)) == -1){
			return 1;
		}
	}
	return 0;
}

long ds_find(int target){
	long loc, i;
	struct ds_list_item_struct list;
	if(ds_read(&loc, 0, sizeof(long)) == NULL){
		return -1;
	}
	i = 0;
	while(loc != -1){
		if(ds_read(&list, loc, sizeof(struct ds_list_item_struct)) == NULL){
			return -1;
		}
		if(list.item == target){
			return i;
		}
		loc = list.next;
		i++;
	}
	return -1;
}

int ds_read_elements(char *filename){
	FILE *fp;
	int num, i;
	fp = fopen(filename, "r");
	if(fp == NULL){
		return 1;
	}
	i = 0;
	while(fscanf(fp, "%d", &num) != EOF){
		if(ds_insert(num, i)){
			return 1;
		}
		i++;
	}
	return 0;
}

int ds_finish_list(){
	return !ds_finish();
}
