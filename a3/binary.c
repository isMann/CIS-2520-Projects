/* 
 * By: Michael Mann
 * ID: 1037704
 * Email: mmann10@uoguelph.ca
 * */
#include "common.h"
#include "binary.h"
#include "name.h"
#include "title.h"
#include "principals.h"

/*
 * add_node() code inspired by the add_node() function in
 * Kremer's fixed_tree.c on courselink.
 */
void add_node(struct tree **root, char *key, void *data){
	if(*root){
		if(strcmp((*root)->key, key) < 0){
			add_node(&((*root)->child[0]), key, data);
		}
		else{
			add_node(&((*root)->child[1]), key, data);
		}
	}
	else{
		(*root) = malloc(sizeof(struct tree));
		(*root)->key = malloc(strlen(key) + 1);
		strcpy((*root)->key, key);
		(*root)->data = data;
		(*root)->child[0] = NULL;
		(*root)->child[1] = NULL;
	}
}


/*
 * find() code inspired by the find() function in
 * Kremer's fixed_tree.c on courselink.
 */
struct tree *find(struct tree *root, char *key){
	if(root){
		if(!strcmp(root->key, key)){
			return root;
		}
		else if(strcmp(root->key, key) < 0){
			return find(root->child[0], key);
		}
		else{
			return find(root->child[1], key);
		}
	}
	else{
		return NULL;
	}
}

void freetree(struct tree *root){
	if(root){
		freetree(root->child[0]);
		freetree(root->child[1]);
		free(root);
	}
}
