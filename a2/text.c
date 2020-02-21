#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/***************************************************************************
 * IMPORTANT VERY IMPORTANT
 * REPEATED OF THE SAME PUNCTIUATION IS ONE WORD
 * ... IS ONE WORD
 * DO NOT FORGET
 * FIX THIS AFTER ALL IS DONE
 * THAT THING IS LIKE 1 MARK PROBABLY SO FIX ALL ELSE FIRST
 * **************************************************************************/
struct node_struct *txt2words(FILE *fp){
	char line[257], word[257];
	struct node_struct *head, *curr;
	int i, j, first;
	curr = head = NULL;
	first = 1;
	word[0] = '\0';
	while(fgets(line, 256, fp) != NULL){
		if(strcmp("\n", line) == 0 || strcmp("\n\r", line) == 0){
			word[0] = line[0];
			word[1] = '\0';
			curr = insertend(curr, word);
			if(first){
				head = curr;
				first = 0;
			}
			word[0] = '\0';
		}
		else{
			for(i = 0; i < strlen(line); i++){
				if(isalnum(line[i]) || line[i] == '\'' || (line[i] == '-' && line[i + 1] != '-')){
					word[strlen(word) + 1] = '\0';
					word[strlen(word)] = line[i];
				}
				else if(line[i] == '-' && line[i + 1] == '-'){
					curr = insertend(curr, word);
					if(first){
						head = curr;
						first = 0;
					}
					strcpy(word, "--");
					i++;
					curr = insertend(curr, word);
					word[0] = '\0';
				}
				else if(line[i] == ' ' || line[i] == '\n' || line[i] == '\t' || line[i] == '\v'
								  || line[i] == '\f' || line[i] == '\r'){
					curr = insertend(curr, word);
					if(first){
						head = curr;
						first = 0;
					}
					word[0] = '\0';
				}
				else if(line[i] == line[i + 1]){
					curr = insertend(curr, word);
					if(first){
						head = curr;
						first = 0;
					}
					j = 0;
					word[j] = line[i];
					j++;
					while(line[i] == line[i + 1]){
						word[j] = line[i];
						word[j + 1] = '\0';
						j++;
						i++;
					}
					curr = insertend(curr, word);
					word[0] = '\0';
				}
				else{
					curr = insertend(curr, word);
					if(first){
						head = curr;
						first = 0;
					}
					word[0] = line[i];
					word[1] = '\0';
					curr = insertend(curr, word);
					word[0] = '\0';
				}
			}
		}
	}
	return head;
}

struct node_struct *search(struct node_struct *list, char *target, int (*compar)(const void *, const void *)){
	struct node_struct *found, *temp, *new;
	temp = list;
	found = NULL;

	while(temp != NULL){
		if((compar((void *)target, temp->data)) == 0){
			if(found == NULL){
				new = malloc(sizeof(struct node_struct));
				found = new;
				new->data = temp;
				new->next = NULL;
			}
			else {
				new->next = malloc(sizeof(struct node_struct));
				new = new->next;
				new->data = temp;
				new->next = NULL;
			}
		}
		temp = temp->next;
	}
	return found;
}
	
struct node_struct *copy(struct node_struct *start, struct node_struct *end){
	struct node_struct *temp, *head, *node;

	temp = start;
	if(temp != NULL){
		node = malloc(sizeof(struct node_struct));
		head = node;
		node->data = temp->data;
		node->next = NULL;
		temp = temp->next;
	}
	else{
		head = NULL;
	}
	while(temp != NULL && temp != end){
		node->next = malloc(sizeof(struct node_struct));
		node = node->next;
		node->data = temp->data;
		node->next = NULL;
		temp = temp->next;
	}
	return head;
}

void ftext(FILE *fp, struct node_struct *list){
	struct node_struct *node;
	char *curr, *next;
	int length, newline;
	length = 0;
	newline = 0;
	node = list;
	while(node != NULL){
		if(node->next != NULL){
			curr = node->data;
			next = node->next->data;
		}
		if(length + strlen((char *)node->data) + 2 >= 80){
			newline = 1;
		}
		fprintf(fp, "%s", (char *)node->data);
		length += strlen((char *)node->data);
		if(node->next != NULL
				&& (!strcmp(curr, ",") || !strcmp(curr, ";") 
				|| !strcmp(curr, "!") || !strcmp(curr, "\"")
				|| !strcmp(curr, ".")) && !(!strcmp(next, "\"")
				|| !strcmp(next, "--"))){
			if(newline){
				fprintf(fp, "\n");
				newline = 0;
				length = 0;
			}
			else{
				fprintf(fp, " ");
			}
		}
		if(node->next != NULL && isalnum(curr[strlen(curr) - 1])
				&& isalnum(next[0])){
			if(newline){
				fprintf(fp, "\n");
				newline = 0;
				length = 0;
			}
			else{
				fprintf(fp, " ");
			}
		}
		node = node->next;
	} 
}

struct node_struct *sort(struct node_struct list, int (*compar)(const void *, const void *)){
	return NULL;
}

void remove_repeats(struct node_struct *list, int (*compar)(const void *, const void *)){
	struct node_struct *curr, *next;
	curr = list;
	if(curr == NULL){
		return;
	}
	while(curr != NULL){
		next = curr->next;
		while(next != NULL && compar(curr->data, next->data) == 0){
			curr->next = next->next;
			free(next);
			next = curr->next;
		}
		curr = next;
	}
}


int length(struct node_struct *list){
	int i;
	if(list == NULL){
		return 0;
	}
	/*This bodyless for loop iterates until it reaches the final node in the list
	 * and increments i every time. */
	for(i = 0; (list = list->next) != NULL; i++);
	i++;
	return i;
}

void free_list(struct node_struct *list, int free_data){
	struct node_struct *temp, *node;
	node = list;
	while(node != NULL){
		temp = node->next;
		if(free_data){
			free(node->data);
		}
		free(node);
		node = temp;
	}
}


struct node_struct *insertend(struct node_struct *list, char *word){
	struct node_struct *temp, *new;
	temp = list;
	if(strlen(word)){
		if (temp == NULL){
			temp = malloc(sizeof(struct node_struct));
			temp->data = malloc(sizeof(strlen(word) + 1));
			strcpy((char *)temp->data, word);
			temp->next = NULL;
		}
		else{
			while(temp->next != NULL){
				temp = temp->next;
			} 
			new = malloc(sizeof(struct node_struct));
			new->data = malloc((strlen(word) + 1));
			strcpy((char *)new->data, word);
			new->next = NULL;
			temp->next = new;
		}
	}
	return temp;
}

void printlist(struct node_struct *head){
	struct node_struct *node;
	node = head;
	while(node != NULL){
		printf("%s", (char *)node->data);
		node = node->next;
	} 
}

int cmp(const void *a, const void *b){
	return strcmp((char *)a, (char *)b);
}

