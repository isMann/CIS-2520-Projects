/* 
 * By: Michael Mann
 * ID: 1037704
 * Email: mmann10@uoguelph.ca
 * */
struct tree{
	char *key;
	void *data;
	struct tree *child[2];
};

void add_node(struct tree **, char *, void *);
struct tree *find(struct tree *, char *);
void freetree(struct tree *);
