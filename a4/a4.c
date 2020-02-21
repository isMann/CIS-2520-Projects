#include "a4.h"
#include <ctype.h>
#include <stdio.h>

int hash1(char *string, int hash_size){
	/* This function was inspired by zybooks Figure 5.7.3
	 * Multiplicative string hash function.
	 * One might say Heavily inspired.
	 */
	unsigned long val;
	val = 57;
	for(;*string;string++){
		val = (val * 31) + *string;
	}
	return val % hash_size;
}
int hash2(char *string, int hash_size){
	unsigned long val, new;
	int col;
	col = 1;
	val = 0;
	for(;*string; string++){
		if(isupper(*string)){
			val += col * (*string - 'A' + 1);
			col *= (27 + '0');
		}
		else if(islower(*string)){
			val += col * (*string - 'a' + 1);
			col *= (27 + '0');
		}
		else if(isdigit(*string)){
			val += col * (*string - '0' + 27);
			col *= (27 + '0');
		}
	}
	/* Code here inspired by the lecture material*/
	while(val){
		new = (val + (new % hash_size)) % hash_size;
		val /= hash_size;
	}
	return new % hash_size;
}
int hash3(char *string, int hash_size){
	int day, month, year;
	int val;
	val = 0;
	if(sscanf(string, "%d/%d/%d", &day, &month, &year) == 3){
		year = ((year >= 2000?200:100)) + year % 100;
		val = day + month * 32 + year * 3200;
	}
	else{
		return hash2(string, hash_size);
	}
	return val % hash_size;
}

int lpow(long val, long i){
	long j;
	for(j = 0; j < i; j++){
		val *= val;
	}
	return val;
}
