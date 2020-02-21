/* 
 * By: Michael Mann
 * ID: 1037704
 * Email: mmann10@uoguelph.ca
 * */
#include "name.h"
#include "common.h"

struct name_basics *get_name(char *path, int *length){
	struct name_basics *array;
	FILE *fp;
	char *filename, *string;
	char line[256];
	int entries;
	
	array = NULL;
	filename = malloc(strlen(path) + strlen("/name.basics.tsv") + 1);
	strcpy(filename, path);
	strcat(filename, "/name.basics.tsv");
	fp = fopen(filename, "r");
	
	entries = 0;
	while(fgets(line, 255, fp)){
		string = getcolumn(line, 4);
		if(strstr(string, "actor") || strstr(string, "actress")){
		       entries++;
		}
	}		
	array = malloc(sizeof(struct name_basics) * entries);
	entries = 0;
	fseek(fp, 0, SEEK_SET);
	while(fgets(line, 255, fp)){
		string = getcolumn(line, 4);
		if(strstr(string, "actor") || strstr(string, "actress")){
			array[entries].nconst = getcolumn(line, 0);
			reverse(&array[entries].nconst);
			array[entries].primaryName = getcolumn(line, 1);
			entries++;
		}
	}
	fclose(fp);
	free(string);
	*length = entries;
	return array;
}

void freenames(struct name_basics *array, int length){
	int i;
	for(i = 0; i < length; i++){
		free(array[i].nconst);
		free(array[i].primaryName);
	}
	free(array);
}
