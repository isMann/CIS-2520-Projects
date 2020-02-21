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

int main(int argc, char **argv){
	struct name_basics *names, *ncon;
	struct title_basics *titles, *tcon;
       	struct title_principals *prins, *pcon;
	int i, nameL, titleL, prinL;
	struct tree *ntree, *ncontree, *ttree, *tcontree, *tprintree, *nprintree, *foundn, *foundt, *foundp;
	char line[256], *in;

	nameL = titleL = prinL = 0;
	
	names = get_name(argv[1], &nameL);
	titles = get_title(argv[1], &titleL);
	prins = get_principals(argv[1], &prinL);


	ntree = ncontree = ttree = tcontree = tprintree = nprintree = NULL;
	for(i = 0; i < nameL; i++){
		add_node(&ntree, names[i].primaryName, &(names[i]));
		add_node(&ncontree, names[i].nconst, &(names[i]));
	}
	for(i = 0; i < titleL; i++){
		add_node(&ttree, titles[i].primaryTitle, &(titles[i]));
		add_node(&tcontree, titles[i].tconst, &(titles[i]));
	}
	for(i = 0; i < prinL; i++){
		add_node(&tprintree, prins[i].tconst, &(prins[i]));
		add_node(&nprintree, prins[i].nconst, &(prins[i]));
	}

	while(1) {
		ncon = NULL;
		tcon = NULL;
		pcon = NULL;
		printf("> ");
		fgets(line, 255, stdin);
		i = 0;
		if((in = strstr(line, "name"))){
			while(isalnum(in[0])){
				in++;
			}
			while(*in == ' ' || *in == '\t'){
				in++;
			}
			removenewline(in);
			foundn = find(ntree, in);
			if(foundn){
				ncon = foundn->data;
				foundp = find(nprintree, ncon->nconst);
				while(foundp){
					pcon = foundp->data;
					foundt = find(tcontree, pcon->tconst);
					if(foundt){
						tcon = foundt->data;
						printf("%s : %s", tcon->primaryTitle, pcon->characters);
					}
					foundp = find(foundp->child[1], ncon->nconst);
				}
			}
		}
		else if((in = strstr(line, "title"))){
			while(isalnum(in[0])){
				in++;
			}
			while(*in == ' ' || *in == '\t'){
				in++;
			}
			removenewline(in);
			foundt = find(ttree, in);
			if(foundt){
				tcon = foundt->data;
				foundp = find(tprintree, tcon->tconst);
				while(foundp){
					pcon = foundp->data;
					foundn = find(ncontree, pcon->nconst);
					if(foundn){
						ncon = foundn->data;
						printf("%s : %s", ncon->primaryName, pcon->characters);
					}
					foundp = find(foundp->child[1], pcon->tconst);
				}
			}
		}
		else{
			break;
		}
	}

	freetree(ntree);
	freetree(ncontree);
	freetree(ttree);
	freetree(tcontree);
	freetree(tprintree);
	freetree(nprintree);
	freenames(names, nameL);
	freetitles(titles, titleL);
	freeprincipals(prins, prinL);
	return 0;
}

