/*
 * Name: Michael Mann
 * ID: 1037704
 * Email mmann10@uoguelph.ca
 */
#define MAX_ELEMENTS 256 

/*array functions*/
int ds_create_array();
int ds_init_array();
int ds_replace(int value, long index);
int ds_insert(int value, long index);
int ds_delete(long index);
int ds_swap(long inxed1, long index2);
long ds_find(int target);
int ds_read_elements(char *filename);
int ds_finish_array();

void showarray();
