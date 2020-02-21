/* 
 * By: Michael Mann
 * ID: 1037704
 * Email: mmann10@uoguelph.ca
 * */
#include "common.h"
#include "principals.h"

struct title_principals *get_principals(char *path, int *length){
	struct title_principals *array;
	FILE *fp;
	char *filename, *string;
	char line[256];
	int entries;

	array = NULL;
	filename = malloc(strlen(path) + strlen("/title.principals.tsv") + 1);
	strcpy(filename, path);
	strcat(filename, "/title.principals.tsv");
	fp = fopen(filename, "r");

	entries = 0;
	while(fgets(line, 255, fp)){
		string = getcolumn(line, 3);
		if(strstr(string, "actor") || strstr(string, "actress")){
		       entries++;
		}
	}		
	array = malloc(sizeof(struct title_principals) * entries);
	entries = 0;
	fseek(fp, 0, SEEK_SET);
	while(fgets(line, 255, fp)){
		string = getcolumn(line, 3);
		if(strstr(string, "actor") || strstr(string, "actress")){
			array = realloc(array, sizeof(struct title_principals) * (entries + 1));
			array[entries].tconst = getcolumn(line, 0);
			reverse(&array[entries].tconst);
			array[entries].nconst = getcolumn(line, 2);
			reverse(&array[entries].nconst);
			array[entries].characters = getcolumn(line, 5);
			entries++;
		}
	}
	fclose(fp);
	*length = entries;
	return array;
}

void freeprincipals(struct title_principals *array, int length){
	int i;
	for(i = 0; i < length; i++){
		free(array[i].nconst);
		free(array[i].tconst);
	}
	free(array);
}
