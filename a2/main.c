#include <stdio.h>
#include "text.h"

int main(){
	FILE *fp;
	struct node_struct *head, *find, *chap1;

	fp = fopen("Dracula.txt", "r");

	head = txt2words(fp);

	find = search(head, "The", cmp);

	printf("%p %p\n", find->data, find->next->data);

	chap1 = copy(find->data, find->next->data);
	ftext(stdout, chap1);

	return 0;
}
