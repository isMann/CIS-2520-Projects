#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "a4.h"

#define BUFFER_SIZE 2048
#define HASH_METHOD 1

int collisions;
int duplicates;

struct record {
    char *last_name;
    char *license_no;
    char *issue_date;
};

struct array {
    struct record *arr;
    int nelements;
    struct record **hash;
    int hash_size;
};

int char2int(unsigned char c) {
    if (isupper(c)) {
        return (int) (c - 'A');
    }
    if (islower(c)) {
        return (int) (c - 'a');
    }
    return 26;
}

int str2int(char *s, int max) {
    char *c;
    unsigned long number, column, new;

    column = 1;
    number = 0;
    for (c = s; (*c); c++) {
        number += char2int(*c) * column;
        column *= 27;
    }

    new = 0;
    while (number) {
        new = (number + (new % max)) % max;
        number = number / max;
    }

    return (int) new;
}

int getIndex(char buffer[], int index) {
    int columnNumber = 0;
    int currentIndex = 0;
    int i = 0;
    while(1){
        if(buffer[i] == '\t'){
            columnNumber++;
            currentIndex = i;
        }

        if (columnNumber == index){
            return currentIndex;
        }

        i++;
    }
}

struct array *read_records() {
    char buffer[BUFFER_SIZE];

    struct array *arrptr;

    FILE *fp;

    int line, start, end;

    arrptr = malloc(sizeof(struct array));
    arrptr->nelements = 0;

    fp = fopen("Professional_and_Occupational_Licensing.tsv", "r");
    fgets(buffer, BUFFER_SIZE, fp);

    while (!feof(fp)) {
        if (fgets(buffer, BUFFER_SIZE, fp) == NULL) {
            break;
        }

        if (strlen(buffer) == BUFFER_SIZE - 1) {
            fprintf(stderr, "Error:  BUFFER TOO SMALL\n");
            exit(-1);
        }

        (arrptr->nelements)++;
    }

    arrptr->arr = malloc(sizeof(struct record) * (arrptr->nelements));

    fseek(fp, 0, SEEK_SET);

    fgets(buffer, BUFFER_SIZE, fp);
    for (line = 0; line < arrptr->nelements; line++) {
        fgets(buffer, BUFFER_SIZE, fp);

        start = getIndex(buffer, 0);
        end = getIndex(buffer, 1);
        (arrptr->arr)[line].last_name = calloc(1, end - start + 1);
        strncpy((arrptr->arr)[line].last_name, buffer + start, end - start);

        start = getIndex(buffer, 3);
        end = getIndex(buffer, 4);
        (arrptr->arr)[line].license_no = calloc(1, end - start + 1);
        strncpy((arrptr->arr)[line].license_no, buffer + start + 1, end - start - 1);

        start = getIndex(buffer, 10);
        end = getIndex(buffer, 11);
        (arrptr->arr)[line].issue_date = calloc(1, end - start + 1);
        strncpy((arrptr->arr)[line].issue_date, buffer + start + 1, end - start - 1);
    }
    return arrptr;
}


void build_hash(struct array *arrptr, int hash_size) {
    int idx, line;
    int duplicate;

    arrptr->hash_size = hash_size;
    arrptr->hash = malloc(sizeof(struct record *) * arrptr->hash_size);

    for (idx = 0; idx < arrptr->hash_size; idx++) {
        (arrptr->hash)[idx] = NULL;
    }

    for (line = 0; line < arrptr->nelements; line++) {
        /*printf( "%d Adding %s\n", line, (arrptr->arr)[line].last_name );*/
        switch (HASH_METHOD) {
            case 1:
                idx = hash1((arrptr->arr)[line].last_name, arrptr->hash_size);
                break;
            case 2:
                idx = hash2((arrptr->arr)[line].license_no, arrptr->hash_size);
                break;
            case 3:
                idx = hash3((arrptr->arr)[line].issue_date, arrptr->hash_size);
                break;
        }

        duplicate = 0;
        while ((arrptr->hash)[idx] != NULL) {
            if (strcmp(((arrptr->hash)[idx])->license_no,
                       (arrptr->arr)[line].license_no) == 0) {
                /*printf( "  Skipping duplicate\n" );*/
                duplicates++;
                duplicate = 1;
                break;
            }
            /*printf( "  collision at %d %s\n", idx, ((arrptr->hash)[idx])->last_name );*/
            collisions++;
            idx++;
            if (idx >= arrptr->hash_size) {
                idx = 0;
            }

        }
        if (!duplicate) {
            /*printf("  inserting at %d\n", idx );*/
            (arrptr->hash)[idx] = (arrptr->arr) + line;
        }
    }

}

void free_array_ptr(struct array *ptr) {
    int i;

    for (i = 0; i < ptr->nelements; i++) {
        free(ptr->arr[i].last_name);
        free(ptr->arr[i].license_no);
        free(ptr->arr[i].issue_date);
    }

    free(ptr->arr);
    free(ptr->hash);

    free(ptr);
}

struct record *find(char *key, struct array *arrptr) {
    int idx;

    switch (HASH_METHOD) {
        case 1:
            idx = hash1(key, arrptr->hash_size);
            break;
        case 2:
            idx = hash2(key, arrptr->hash_size);
            break;
        case 3:
            idx = hash3(key, arrptr->hash_size);
            break;
    }

    while ((arrptr->hash)[idx] != NULL) {
        if (strcmp(key, ((arrptr->hash)[idx])->license_no) == 0) {
            return (arrptr->hash)[idx];
        }
        idx++;

        if (idx >= (arrptr->hash_size)) {
            idx = 0;
        }
    }
    return NULL;

}


int main() {
    struct array *arrptr;
    struct record *r;

    collisions = 0;
    duplicates = 0;

    arrptr = read_records();

    build_hash(arrptr, 500000);

    printf("Duplicates: %d\n", duplicates);
    printf("Collisions: %d\n", collisions);

    r = find("Kremer", arrptr);

    if (r == NULL) {
        printf("Not found\n");
    } else {
        printf("%s : %s : %s\n", r->last_name, r->license_no, r->issue_date);
    }

    free_array_ptr(arrptr);
    return 0;
}
