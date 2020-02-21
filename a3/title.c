/* 
 * By: Michael Mann
 * ID: 1037704
 * Email: mmann10@uoguelph.ca
 * */
#include "common.h"
#include "title.h"

struct title_basics *get_title(char *path, int *length){
	struct title_basics *array;
	FILE *fp;
	char *filename, *type, *isAdult;
	char line[256];
	int entries;

	array = NULL;
	filename = malloc(strlen(path) + strlen("/title.basics.tsv") + 1);
	strcpy(filename, path);
	strcat(filename, "/title.basics.tsv");
	fp = fopen(filename, "r");

	entries = 0;
	while(fgets(line, 255, fp)){
		type = getcolumn(line, 1);
		isAdult = getcolumn(line, 4);
		if(strstr(type, "movie") && *isAdult == '0'){
			entries++;
		}
	}
	array = malloc(sizeof(struct title_basics) * entries);
	entries = 0;
	fseek(fp, 0, SEEK_SET);
	while(fgets(line, 255, fp)){
		type = getcolumn(line, 1);
		isAdult = getcolumn(line, 4);
		if(strstr(type, "movie") && *isAdult == '0'){
			array[entries].tconst = getcolumn(line, 0);
			reverse(&array[entries].tconst);
			array[entries].primaryTitle = getcolumn(line, 2);
			entries++;
		}
	}
	fclose(fp);
	*length = entries;
	return array;
}

void freetitles(struct title_basics *array, int length){
	int i;
	for(i = 0; i < length; i++){
		free(array[i].tconst);
		free(array[i].primaryTitle);
	}
	free(array);
}
