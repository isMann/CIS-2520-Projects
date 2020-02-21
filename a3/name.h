/* 
 * By: Michael Mann
 * ID: 1037704
 * Email: mmann10@uoguelph.ca
 * */
struct name_basics{
	char *nconst;
	char *primaryName;
};

struct name_basics *get_name(char *, int *);
void freenames(struct name_basics *, int);
