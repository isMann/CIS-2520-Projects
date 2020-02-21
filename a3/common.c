/* 
 * By: Michael Mann
 * ID: 1037704
 * Email: mmann10@uoguelph.ca
 * */
#include "common.h"

char *getcolumn(char *line, int colnum){
	int start, end, i;
	char *string;

	end = 0;
	for(i = 0; i < colnum; i++){
		for(end = end; !(line[end] == '\t' || line[end] == '\0'); end++);
		end++;
	}
	start = end;

	for(end = end; !(line[end] == '\t' || line[end] == '\0'); end++);
	string = malloc(end - start + 1);
	for(i = 0; start < end; start++){
		string[i] = line[start];
		i++;
	}
	string[i] = '\0';		
	return string;
}

void removenewline(char *string){
	for(; *string != '\n'; string++);
	*string = '\0';
}

void reverse(char **string){
	char temp;
	int i;
	for(i = 0; i < strlen((*string))/2; i++){
		temp = (*string)[i];
		(*string)[i] = (*string)[strlen(*string) - i - 1];
		(*string)[strlen(*string) - i - 1] = temp;
	}
}
