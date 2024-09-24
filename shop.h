#ifndef SHOP_H_
#define SHOP_H_
#include <stdio.h>

typedef struct product Product;
struct product{
  float price;
  long int code;
  char* name;
};

typedef struct data Data;
struct data{

};

typedef struct storeEntry StoreEntry;
struct storeEntry{

};

/*
  Reads at most max_size_with_null - 1 chars into an array, and terminates with a '\0'
  returns the amount of characters read;
 */
unsigned int my_getline(const unsigned int max_size_with_null, char arr[max_size_with_null], FILE* file_ptr);

/*
  returns an array of strings read from the const char* filename
 */
char **scan_file(char *filename, int *scanned_elements);

/*
  frees unused elements
  i.e if 50 elements were scanned, 100 were max,
  then frees all the elements with indexes <50, 99>
 */
void free_unused_cells(char** data, int scanned_elements, const int max_data_elements);

/*
  frees the array of strings
 */
void free_data(char** data, const int elem_number);


#endif // SHOP_H_
