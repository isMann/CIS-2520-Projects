/* 
 * By: Michael Mann
 * ID: 1037704
 * Email: mmann10@uoguelph.ca
 * */
struct title_basics{
	char *tconst;
	char *primaryTitle;
};

struct title_basics *get_title(char *, int *);
void freetitles(struct title_basics*, int);
