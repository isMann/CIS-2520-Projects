/* 
 * By: Michael Mann
 * ID: 1037704
 * Email: mmann10@uoguelph.ca
 * */
struct title_principals{
	char *tconst;
	char *nconst;
	char *characters;
};

struct title_principals *get_principals(char *, int *);
void freeprincipals(struct title_principals *, int);
